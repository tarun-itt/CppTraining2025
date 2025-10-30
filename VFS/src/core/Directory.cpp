#include <algorithm>
#include <ctime>

#include "Directory.h"
#include "File.h"
#include "FileSystemNode.h"

Directory::Directory(const std::string &name) : FileSystemNode(name) {}

size_t Directory::getSize() const {
    size_t totalSize = 0;
    for (const auto &child : children) {
        totalSize += child->getSize();
    }
    return totalSize;
}

void Directory::addChild(std::shared_ptr<FileSystemNode> child) {
    if (!child || hasChild(child->getName())) {
        return;
    }

    children.push_back(child);
    childIndex[child->getName()] = children.size() - 1;
    updateModificationTime();
}

bool Directory::removeChild(const std::string &name) {
    auto searchedChildNode = childIndex.find(name);
    if (searchedChildNode == childIndex.end()) {
        return false;
    }

    children.erase(children.begin() + searchedChildNode->second);
    rebuildIndex();
    updateModificationTime();
    return true;
}

std::shared_ptr<FileSystemNode> Directory::getChild(const std::string &name) const {
    auto searchedChildNode = childIndex.find(name);
    if (searchedChildNode != childIndex.end() && searchedChildNode->second < children.size()) {
        return children[searchedChildNode->second];
    }
    return nullptr;
}

bool Directory::hasChild(const std::string &name) const {
    return childIndex.find(name) != childIndex.end();
}

std::vector<std::shared_ptr<FileSystemNode>> Directory::findByName(const std::string &name) const {
    std::vector<std::shared_ptr<FileSystemNode>> result;

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

std::vector<std::shared_ptr<FileSystemNode>> Directory::findBySize(size_t minSize, size_t maxSize) const {
    std::vector<std::shared_ptr<FileSystemNode>> result;

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

std::vector<std::shared_ptr<FileSystemNode>> Directory::findByTimestamp(time_t start, time_t end) const {
    std::vector<std::shared_ptr<FileSystemNode>> result;

    for (const auto &child : children) {
        time_t modTime = child->getModificationTime();
        if (modTime >= start && modTime <= end) {
            result.push_back(child);
        }

        if (child->isDirectory()) {
            auto childDir = std::dynamic_pointer_cast<Directory>(child);
            if (childDir) {
                auto resultFromChild = childDir->findByTimestamp(start, end);
                result.insert(result.end(), resultFromChild.begin(), resultFromChild.end());
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