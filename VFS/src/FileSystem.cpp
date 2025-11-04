#include <sstream>

#include "FileSystem.h"
#include "File.h"
#include "Directory.h"
#include "FileSystemPersistence.h"

FileSystem::FileSystem(std::unique_ptr<FileSystemPersistence> persistence) 
    : fileSystemStateStorage(std::move(persistence)) {
}

FileSystem::~FileSystem() = default;

void FileSystem::initialize() {
    root = std::make_shared<Directory>("root");
    currentDirectory = root;
    currentPathComponents = {"/"};
}

void FileSystem::saveFileSystem() {
    if (fileSystemStateStorage) {
        fileSystemStateStorage->saveFileSystem(*this);
    }
}

void FileSystem::loadFileSystem() {
    if (fileSystemStateStorage) {
        fileSystemStateStorage->loadFileSystem(*this);
    }
}

bool FileSystem::createDirectory(const std::string &path) {
    if (path.empty()) return false;

    std::string dirName;
    auto parentDir = resolveParentDirectory(path, dirName);
    if (!parentDir) return false;

    if (parentDir->hasChild(dirName)) return false;

    auto newDir = std::make_shared<Directory>(dirName);
    parentDir->addChild(newDir);
    return true;
}

bool FileSystem::createFile(const std::string &path, const std::string &content) {
    if (path.empty()) return false;

    std::string fileName;
    auto parentDir = resolveParentDirectory(path, fileName);
    if (!parentDir) return false;

    if (parentDir->hasChild(fileName)) return false;

    auto newFile = std::make_shared<File>(fileName, content);
    parentDir->addChild(newFile);
    return true;
}

bool FileSystem::removeFile(const std::string &path) {
    auto obj = getFileSystemComponent(path);
    if (!obj || obj->isDirectory()) return false;

    std::string fileName;
    auto parentDir = resolveParentDirectory(path, fileName);
    if (!parentDir) return false;

    return parentDir->removeChild(fileName);
}

bool FileSystem::removeDir(const std::string &path) {
    auto obj = getFileSystemComponent(path);
    if (!obj || !obj->isDirectory()) return false;

    std::string dirName;
    auto parentDir = resolveParentDirectory(path, dirName);
    if (!parentDir) return false;

    return parentDir->removeChild(dirName);
}

bool FileSystem::changeDir(const std::string &path) {
    if (path == "/") {
        currentDirectory = root;
        currentPathComponents = {"/"};
        return true;
    }

    auto dir = getDirectory(path);
    if (!dir) return false;

    if (!path.empty() && path.front() == '/') {
        currentPathComponents.clear();
        currentPathComponents.push_back("/");
        auto comps = splitPathToComponents(path);
        currentPathComponents.insert(currentPathComponents.end(), comps.begin(), comps.end());
    } else {
        auto pathComponents = splitPathToComponents(path);
        for (const auto &component : pathComponents) {
            if (component == "..") {
                if (currentPathComponents.size() > 1) {
                    currentPathComponents.pop_back();
                }
            } else if (component != ".") {
                currentPathComponents.push_back(component);
            }
        }
    }

    currentDirectory = dir;
    return true;
}

bool FileSystem::exists(const std::string &path) const {
    return getFileSystemComponent(path) != nullptr;
}

std::shared_ptr<FileSystemComponent> FileSystem::getFileSystemComponent(const std::string &path) const {
    if (path == "/" || path.empty()) {
        return root;
    }

    auto pathComponents = splitPathToComponents(path);
    std::shared_ptr<FileSystemComponent> current;
    
    if (path.front() != '/') {
        auto resolvedPath = currentPathComponents;
        for (const auto &component : pathComponents) {
            if (component == "..") {
                if (resolvedPath.size() > 1) {
                    resolvedPath.pop_back();
                }
            } else if (component != ".") {
                resolvedPath.push_back(component);
            }
        }
        
        current = root;
        for (size_t i = 1; i < resolvedPath.size(); ++i) {
            if (!current || !current->isDirectory()) {
                return nullptr;
            }
            auto dir = std::dynamic_pointer_cast<Directory>(current);
            current = dir->getChild(resolvedPath[i]);
        }
        return current;
    }
    
    current = root;
    for (const auto &component : pathComponents) {
        if (!current || !current->isDirectory()) {
            return nullptr;
        }

        auto dir = std::dynamic_pointer_cast<Directory>(current);
        if (component == "..") {
            return nullptr;
        } else if (component == ".") {
            continue;
        } else {
            current = dir->getChild(component);
        }
    }

    return current;
}

std::shared_ptr<File> FileSystem::getFile(const std::string &path) const {
    auto obj = getFileSystemComponent(path);
    if (obj && obj->isFile()) {
        return std::dynamic_pointer_cast<File>(obj);
    }
    return nullptr;
}

std::shared_ptr<Directory> FileSystem::getDirectory(const std::string &path) const {
    auto obj = getFileSystemComponent(path);
    if (obj && obj->isDirectory()) {
        return std::dynamic_pointer_cast<Directory>(obj);
    }
    return nullptr;
}

std::string FileSystem::getCurrentPath() const {
    return joinPath(currentPathComponents);
}

std::shared_ptr<Directory> FileSystem::getCurrentDirectory() const {
    return currentDirectory;
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

std::vector<std::string> FileSystem::splitPathToComponents(const std::string &path) const {
    std::vector<std::string> pathComponents;
    
    if (path.empty() || path == "/") {
        return pathComponents;
    }

    std::string cleanPath = path;
    if (cleanPath.front() == '/') {
        cleanPath = cleanPath.substr(1);
    }

    std::istringstream stream(cleanPath);
    std::string component;
    
    while (std::getline(stream, component, '/')) {
        if (!component.empty() && component != ".") {
            pathComponents.push_back(component);
        }
    }

    return pathComponents;
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

std::shared_ptr<Directory> FileSystem::resolveParentDirectory(const std::string &path, std::string &outName) const {
    if (path.empty()) return nullptr;

    bool isAbsolute = (path.front() == '/');
    auto pathComponents = splitPathToComponents(path);
    
    if (pathComponents.empty()) return nullptr;

    outName = pathComponents.back();
    pathComponents.pop_back();

    if (pathComponents.empty()) {
        return isAbsolute ? root : currentDirectory;
    }

    std::string parentPath;
    if (isAbsolute) {
        std::vector<std::string> absolutePath = {"/"};
        absolutePath.insert(absolutePath.end(), pathComponents.begin(), pathComponents.end());
        parentPath = joinPath(absolutePath);
    } else {
        for (size_t i = 0; i < pathComponents.size(); ++i) {
            if (i > 0) parentPath += "/";
            parentPath += pathComponents[i];
        }
    }

    return getDirectory(parentPath);
}