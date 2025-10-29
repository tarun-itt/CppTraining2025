#include <algorithm>
#include <ctime>

#include "Directory.h"
#include "File.h"
#include "FileSystemObject.h"

Directory::Directory(const std::string &name) : FileSystemObject(name) {}

size_t Directory::getSize() const {
    size_t totalSize = 0;
    for (const auto &child : children) {
        totalSize += child->getSize();
    }
    return totalSize;
}

void Directory::addChild(std::shared_ptr<FileSystemObject> child) {
    if (!child || hasChild(child->getName())) {
        return;
    }

    children.push_back(child);
    childIndex[child->getName()] = children.size() - 1;
    updateModificationTime();
}

bool Directory::removeChild(const std::string &name) {
    auto it = childIndex.find(name);
    if (it == childIndex.end()) {
        return false;
    }

    children.erase(children.begin() + it->second);
    rebuildIndex();
    updateModificationTime();
    return true;
}

std::shared_ptr<FileSystemObject> Directory::getChild(const std::string &name) const {
    auto it = childIndex.find(name);
    if (it != childIndex.end() && it->second < children.size()) {
        return children[it->second];
    }
    return nullptr;
}

bool Directory::hasChild(const std::string &name) const {
    return childIndex.find(name) != childIndex.end();
}

std::vector<std::shared_ptr<FileSystemObject>> Directory::findByName(const std::string &name) const {
    std::vector<std::shared_ptr<FileSystemObject>> result;

    for (const auto &child : children) {
        if (child->getName() == name) {
            result.push_back(child);
        }

        if (child->isDirectory()) {
            auto childDir = std::dynamic_pointer_cast<Directory>(child);
            if (childDir) {
                auto childResults = childDir->findByName(name);
                result.insert(result.end(), childResults.begin(), childResults.end());
            }
        }
    }
    return result;
}

std::vector<std::shared_ptr<FileSystemObject>> Directory::findBySize(size_t minSize, size_t maxSize) const {
    std::vector<std::shared_ptr<FileSystemObject>> result;

    for (const auto &child : children) {
        size_t size = child->getSize();
        if (size >= minSize && size <= maxSize) {
            result.push_back(child);
        }

        if (child->isDirectory()) {
            auto childDir = std::dynamic_pointer_cast<Directory>(child);
            if (childDir) {
                auto childResults = childDir->findBySize(minSize, maxSize);
                result.insert(result.end(), childResults.begin(), childResults.end());
            }
        }
    }
    return result;
}

std::vector<std::shared_ptr<FileSystemObject>> Directory::findByTimestamp(time_t start, time_t end) const {
    std::vector<std::shared_ptr<FileSystemObject>> result;

    for (const auto &child : children) {
        time_t modTime = child->getModificationTime();
        if (modTime >= start && modTime <= end) {
            result.push_back(child);
        }

        if (child->isDirectory()) {
            auto childDir = std::dynamic_pointer_cast<Directory>(child);
            if (childDir) {
                auto childResults = childDir->findByTimestamp(start, end);
                result.insert(result.end(), childResults.begin(), childResults.end());
            }
        }
    }
    return result;
}

void Directory::rebuildIndex() {
    childIndex.clear();
    for (size_t i = 0; i < children.size(); ++i) {
        childIndex[children[i]->getName()] = i;
    }
}