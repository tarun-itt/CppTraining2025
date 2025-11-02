#include <sstream>

#include "../inc/FileSystem.h"
#include "../inc/File.h"
#include "../inc/Directory.h"
#include "../inc/FileSystemPersistence.h"

FileSystem::FileSystem(std::unique_ptr<FileSystemPersistence> persistence) 
    : persistence(std::move(persistence)) {
}

FileSystem::~FileSystem() = default;

void FileSystem::initialize() {
    root = std::make_shared<Directory>("root");
    currentDirectory = root;
    currentPath = {"/"};
}

void FileSystem::saveFileSystem() {
    if (persistence) {
        persistence->saveFileSystem(*this);
    }
}

void FileSystem::loadFileSystem() {
    if (persistence) {
        persistence->loadFileSystem(*this);
    }
}

bool FileSystem::createDirectory(const std::string &path) {
    auto pathComponents = parsePath(path);
    if (pathComponents.empty()) return false;

    std::string dirName = pathComponents.back();
    pathComponents.pop_back();

    std::shared_ptr<Directory> parentDir;
    if (pathComponents.empty()) {
        parentDir = currentDirectory;
    } else {
        parentDir = navigateToParent(pathComponents);
        if (!parentDir) return false;
    }

    if (parentDir->hasChild(dirName)) return false;

    auto newDir = std::make_shared<Directory>(dirName);
    parentDir->addChild(newDir);
    return true;
}

bool FileSystem::createFile(const std::string &path, const std::string &content) {
    auto pathComponents = parsePath(path);
    if (pathComponents.empty()) return false;

    std::string fileName = pathComponents.back();
    pathComponents.pop_back();

    std::shared_ptr<Directory> parentDir;
    if (pathComponents.empty()) {
        parentDir = currentDirectory;
    } else {
        parentDir = navigateToParent(pathComponents);
        if (!parentDir) return false;
    }

    if (parentDir->hasChild(fileName)) return false;

    auto newFile = std::make_shared<File>(fileName, content);
    parentDir->addChild(newFile);
    return true;
}

bool FileSystem::removeFile(const std::string &path) {
    auto obj = getObject(path);
    if (!obj || obj->isDirectory()) return false;

    auto pathComponents = parsePath(path);
    if (pathComponents.empty()) return false;

    std::string fileName = pathComponents.back();
    pathComponents.pop_back();

    std::shared_ptr<Directory> parentDir;
    if (pathComponents.empty()) {
        parentDir = currentDirectory;
    } else {
        parentDir = navigateToParent(pathComponents);
        if (!parentDir) return false;
    }

    return parentDir->removeChild(fileName);
}

bool FileSystem::removeDir(const std::string &path) {
    auto obj = getObject(path);
    if (!obj || !obj->isDirectory()) return false;

    auto pathComponents = parsePath(path);
    if (pathComponents.empty()) return false;

    std::string dirName = pathComponents.back();
    pathComponents.pop_back();

    std::shared_ptr<Directory> parentDir;
    if (pathComponents.empty()) {
        parentDir = currentDirectory;
    } else {
        parentDir = navigateToParent(pathComponents);
        if (!parentDir) return false;
    }

    return parentDir->removeChild(dirName);
}

bool FileSystem::changeDir(const std::string &path) {
    if (path == "/") {
        currentDirectory = root;
        currentPath = {"/"};
        return true;
    }

    auto dir = getDirectory(path);
    if (!dir) return false;

    currentDirectory = dir;
    
    // Update current path
    if (path.front() == '/') {
        // Absolute path
        currentPath = parsePath(path);
        if (currentPath.empty()) currentPath = {"/"};
    } else {
        // Relative path
        auto pathComponents = parsePath(path);
        for (const auto &component : pathComponents) {
            if (component == "..") {
                if (currentPath.size() > 1) {
                    currentPath.pop_back();
                }
            } else if (component != ".") {
                currentPath.push_back(component);
            }
        }
        
        // Update currentDirectory to match the new currentPath
        std::string newPath = joinPath(currentPath);
        currentDirectory = getDirectory(newPath);
        if (!currentDirectory) {
            // This should not happen, but fallback to root if it does
            currentDirectory = root;
            currentPath = {"/"};
        }
    }

    return true;
}

bool FileSystem::exists(const std::string &path) const {
    return getObject(path) != nullptr;
}

std::shared_ptr<FileSystemComponent> FileSystem::getObject(const std::string &path) const {
    if (path == "/" || path.empty()) {
        return root;
    }

    auto pathComponents = parsePath(path);
    std::shared_ptr<FileSystemComponent> current;
    
    // For relative paths, we need to resolve them relative to currentPath first
    if (path.front() != '/') {
        // Relative path - build absolute path by combining currentPath with relative path
        auto resolvedPath = currentPath;
        for (const auto &component : pathComponents) {
            if (component == "..") {
                if (resolvedPath.size() > 1) {
                    resolvedPath.pop_back();
                }
            } else if (component != ".") {
                resolvedPath.push_back(component);
            }
        }
        
        // Now traverse from root using the resolved absolute path
        current = root;
        for (size_t i = 1; i < resolvedPath.size(); ++i) { // Start from 1 to skip root "/"
            if (!current || !current->isDirectory()) {
                return nullptr;
            }
            auto dir = std::dynamic_pointer_cast<Directory>(current);
            current = dir->getChild(resolvedPath[i]);
        }
        return current;
    }
    
    // Absolute path - start from root and traverse
    current = root;
    for (const auto &component : pathComponents) {
        if (!current || !current->isDirectory()) {
            return nullptr;
        }

        auto dir = std::dynamic_pointer_cast<Directory>(current);
        if (component == "..") {
            // For absolute paths, we can't implement .. without parent pointers
            // This would require a more complex directory structure
            return nullptr;
        } else if (component == ".") {
            // Current directory - no change needed
            continue;
        } else {
            current = dir->getChild(component);
        }
    }

    return current;
}

std::shared_ptr<File> FileSystem::getFile(const std::string &path) const {
    auto obj = getObject(path);
    if (obj && obj->isFile()) {
        return std::dynamic_pointer_cast<File>(obj);
    }
    return nullptr;
}

std::shared_ptr<Directory> FileSystem::getDirectory(const std::string &path) const {
    auto obj = getObject(path);
    if (obj && obj->isDirectory()) {
        return std::dynamic_pointer_cast<Directory>(obj);
    }
    return nullptr;
}

std::string FileSystem::getCurrentPath() const {
    return joinPath(currentPath);
}

std::vector<std::shared_ptr<FileSystemComponent>> FileSystem::listCurrentDirectory() const {
    return currentDirectory->getChildren();
}

std::string FileSystem::readFile(const std::string &path) const {
    auto file = getFile(path);
    return file ? file->getContent() : "";
}

bool FileSystem::writeFile(const std::string &path, const std::string &content) {
    auto file = getFile(path);
    if (file) {
        file->setContent(content);
        return true;
    }
    return false;
}

bool FileSystem::appendToFile(const std::string &path, const std::string &content) {
    auto file = getFile(path);
    if (file) {
        file->appendContent(content);
        return true;
    }
    return false;
}

std::vector<std::shared_ptr<FileSystemComponent>> FileSystem::findByName(const std::string &name) const {
    return root->findByName(name);
}

std::vector<std::shared_ptr<FileSystemComponent>> FileSystem::findBySize(std::size_t minSize, std::size_t maxSize) const {
    return root->findBySize(minSize, maxSize);
}

std::vector<std::shared_ptr<FileSystemComponent>> FileSystem::findByTimestamp(std::time_t start, std::time_t end) const {
    return root->findByTimestamp(start, end);
}

std::vector<std::shared_ptr<FileSystemComponent>> FileSystem::findByContent(const std::string &pattern) const {
    std::vector<std::shared_ptr<FileSystemComponent>> results;
    // This would need to be implemented to search all files
    return results;
}

std::vector<std::string> FileSystem::searchLines(const std::string &pattern) const {
    std::vector<std::string> results;
    // This would need to be implemented to search all files
    return results;
}

std::vector<std::string> FileSystem::parsePath(const std::string &path) const {
    std::vector<std::string> components;
    
    if (path.empty() || path == "/") {
        return components;
    }

    std::string cleanPath = path;
    if (cleanPath.front() == '/') {
        cleanPath = cleanPath.substr(1);
    }

    std::istringstream stream(cleanPath);
    std::string component;
    
    while (std::getline(stream, component, '/')) {
        if (!component.empty() && component != ".") {
            components.push_back(component);
        }
    }

    return components;
}

std::shared_ptr<Directory> FileSystem::navigateToParent(const std::vector<std::string> &pathComponents) const {
    std::shared_ptr<FileSystemComponent> current = root;

    for (const auto &component : pathComponents) {
        if (!current || !current->isDirectory()) {
            return nullptr;
        }

        auto dir = std::dynamic_pointer_cast<Directory>(current);
        current = dir->getChild(component);
    }

    return std::dynamic_pointer_cast<Directory>(current);
}

std::string FileSystem::joinPath(const std::vector<std::string> &pathComponents) const {
    if (pathComponents.empty() || (pathComponents.size() == 1 && pathComponents[0] == "/")) {
        return "/";
    }

    std::string result;
    for (const auto &component : pathComponents) {
        if (component != "/") {
            result += "/" + component;
        }
    }

    return result.empty() ? "/" : result;
}