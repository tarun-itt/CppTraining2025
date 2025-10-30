#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "FileSystemManager.h"

FileSystemManager::FileSystemManager(std::unique_ptr<IPersistenceStrategy> persistence)
    : persistence(std::move(persistence)) {
    initialize();
}

FileSystemManager::~FileSystemManager() {
    save();
}

void FileSystemManager::initialize() {
    if (persistence && persistence->exists()) {
        load();
    } else {
        root = std::make_shared<Directory>("root");
    }

    if (!root) {
        root = std::make_shared<Directory>("root");
    }

    currentDirectory = root;
    currentPath = {};
}

void FileSystemManager::save() {
    if (persistence && root) {
        persistence->saveFileSystem(root);
    }
}

void FileSystemManager::load() {
    if (persistence) {
        auto loaded = persistence->loadFileSystem();
        if (loaded && loaded->isDirectory()) {
            root = std::dynamic_pointer_cast<Directory>(loaded);
            currentDirectory = root;
            currentPath.clear();
        }
    }
}

bool FileSystemManager::createDirectory(const std::string &path) {
    auto pathComponents = splitPath(path);
    if (pathComponents.empty())
        return false;

    auto parentPath = pathComponents;
    std::string dirName = parentPath.back();
    parentPath.pop_back();

    std::shared_ptr<Directory> parentDir;
    if (parentPath.empty()) {
        parentDir = currentDirectory;
    } else {
        auto parent = navigateToPath(joinPath(parentPath));
        if (!parent || !parent->isDirectory())
            return false;
        parentDir = std::dynamic_pointer_cast<Directory>(parent);
    }

    if (parentDir->hasChild(dirName))
        return false;

    auto newDir = std::make_shared<Directory>(dirName);
    parentDir->addChild(newDir);
    return true;
}

bool FileSystemManager::createFile(const std::string &path, const std::string &content) {
    auto pathComponents = splitPath(path);
    if (pathComponents.empty())
        return false;

    auto parentPath = pathComponents;
    std::string fileName = parentPath.back();
    parentPath.pop_back();

    std::shared_ptr<Directory> parentDir;
    if (parentPath.empty()) {
        parentDir = currentDirectory;
    } else {
        auto parent = navigateToPath(joinPath(parentPath));
        if (!parent || !parent->isDirectory())
            return false;
        parentDir = std::dynamic_pointer_cast<Directory>(parent);
    }

    if (parentDir->hasChild(fileName))
        return false;

    auto newFile = std::make_shared<File>(fileName, content);
    parentDir->addChild(newFile);
    return true;
}

bool FileSystemManager::remove(const std::string &path) {
    auto pathComponents = splitPath(path);
    if (pathComponents.empty())
        return false;

    auto parentPath = pathComponents;
    std::string objectName = parentPath.back();
    parentPath.pop_back();

    std::shared_ptr<Directory> parentDir;
    if (parentPath.empty()) {
        parentDir = currentDirectory;
    } else {
        auto parent = navigateToPath(joinPath(parentPath));
        if (!parent || !parent->isDirectory())
            return false;
        parentDir = std::dynamic_pointer_cast<Directory>(parent);
    }

    return parentDir->removeChild(objectName);
}

bool FileSystemManager::changeDirectory(const std::string &path) {
    if (path == "..") {
        if (!currentPath.empty()) {
            currentPath.pop_back();
            if (currentPath.empty()) {
                currentDirectory = root;
            } else {
                auto newCurrent = navigateToPath(joinPath(currentPath));
                if (newCurrent && newCurrent->isDirectory()) {
                    currentDirectory = std::dynamic_pointer_cast<Directory>(newCurrent);
                }
            }
        }
        return true;
    }

    auto target = navigateToPath(path);
    if (!target || !target->isDirectory())
        return false;

    currentDirectory = std::dynamic_pointer_cast<Directory>(target);
    if (isAbsolutePath(path)) {
        currentPath = splitPath(path);
    } else {
        auto pathComponents = splitPath(path);
        currentPath.insert(currentPath.end(), pathComponents.begin(), pathComponents.end());
    }
    return true;
}

bool FileSystemManager::exists(const std::string &path) const {
    return navigateToPath(path) != nullptr;
}

std::shared_ptr<FileSystemNode> FileSystemManager::getObject(const std::string &path) const {
    return navigateToPath(path);
}

std::shared_ptr<File> FileSystemManager::getFile(const std::string &path) const {
    auto obj = navigateToPath(path);
    if (obj && obj->isFile()) {
        return std::dynamic_pointer_cast<File>(obj);
    }
    return nullptr;
}

std::shared_ptr<Directory> FileSystemManager::getDirectory(const std::string &path) const {
    auto obj = navigateToPath(path);
    if (obj && obj->isDirectory()) {
        return std::dynamic_pointer_cast<Directory>(obj);
    }
    return nullptr;
}

std::string FileSystemManager::getCurrentPath() const {
    if (currentPath.empty())
        return "/";
    return "/" + joinPath(currentPath);
}

std::vector<std::shared_ptr<FileSystemNode>> FileSystemManager::listCurrentDirectory() const {
    return currentDirectory->getChildren();
}

std::string FileSystemManager::readFile(const std::string &path) const {
    auto file = getFile(path);
    return file ? file->getContent() : "";
}

bool FileSystemManager::writeFile(const std::string &path, const std::string &content) {
    auto file = getFile(path);
    if (file) {
        file->setContent(content);
        return true;
    }
    return false;
}

bool FileSystemManager::appendToFile(const std::string &path, const std::string &content) {
    auto file = getFile(path);
    if (file) {
        file->appendContent(content);
        return true;
    }
    return false;
}

std::vector<std::shared_ptr<FileSystemNode>> FileSystemManager::findByName(const std::string &name) const {
    return root->findByName(name);
}

std::vector<std::shared_ptr<FileSystemNode>> FileSystemManager::findBySize(size_t minSize, size_t maxSize) const {
    return root->findBySize(minSize, maxSize);
}

std::vector<std::shared_ptr<FileSystemNode>> FileSystemManager::findByTimestamp(time_t start, time_t end) const {
    return root->findByTimestamp(start, end);
}

std::vector<std::shared_ptr<FileSystemNode>> FileSystemManager::findByContent(const std::string &pattern) const {
    std::vector<std::shared_ptr<FileSystemNode>> results;
    collectContentSearchableObjects(root, results, pattern);
    return results;
}

std::vector<std::string> FileSystemManager::searchLines(const std::string &pattern) const {
    std::vector<std::string> allLines;
    auto files = findByContent(pattern);

    for (const auto &obj : files) {
        if (obj->isFile()) {
            auto file = std::dynamic_pointer_cast<File>(obj);
            if (file) {
                auto lines = file->searchLines(pattern);
                allLines.insert(allLines.end(), lines.begin(), lines.end());
            }
        }
    }
    return allLines;
}

std::shared_ptr<FileSystemNode> FileSystemManager::navigateToPath(const std::string &path) const {
    if (path.empty() || path == "/")
        return root;

    auto pathComponents = splitPath(path);
    std::shared_ptr<FileSystemNode> current = isAbsolutePath(path) ? root : currentDirectory;

    for (const auto &component : pathComponents) {
        if (!current || !current->isDirectory())
            return nullptr;

        auto dir = std::dynamic_pointer_cast<Directory>(current);
        current = dir->getChild(component);
    }

    return current;
}

std::vector<std::string> FileSystemManager::splitPath(const std::string &path) const {
    std::vector<std::string> components;
    std::istringstream stream(path);
    std::string component;

    while (std::getline(stream, component, '/')) {
        if (!component.empty()) {
            components.push_back(component);
        }
    }
    return components;
}

std::string FileSystemManager::joinPath(const std::vector<std::string> &pathComponents) const {
    if (pathComponents.empty())
        return "";

    std::ostringstream result;
    for (size_t i = 0; i < pathComponents.size(); ++i) {
        if (i > 0)
            result << "/";
        result << pathComponents[i];
    }
    return result.str();
}

bool FileSystemManager::isAbsolutePath(const std::string &path) const {
    return !path.empty() && path[0] == '/';
}

void FileSystemManager::collectContentSearchableObjects(const std::shared_ptr<FileSystemNode> &node,
                                                        std::vector<std::shared_ptr<FileSystemNode>> &results,
                                                        const std::string &pattern) const {
    if (node->isFile()) {
        auto file = std::dynamic_pointer_cast<File>(node);
        if (file) {
            auto fileResults = file->findByContent(pattern);
            results.insert(results.end(), fileResults.begin(), fileResults.end());
        }
    } else if (node->isDirectory()) {
        auto dir = std::dynamic_pointer_cast<Directory>(node);
        if (dir) {
            for (const auto &child : dir->getChildren()) {
                collectContentSearchableObjects(child, results, pattern);
            }
        }
    }
}