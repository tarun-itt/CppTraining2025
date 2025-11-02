#include <ctime>
#include <algorithm>

#include "../inc/Directory.h"

Directory::Directory(const std::string &name) : name(name) {
    creationTime = std::time(nullptr);
    modificationTime = creationTime;
}

std::size_t Directory::getSize() const {
    std::size_t totalSize = 0;
    for (const auto &child : children) {
        totalSize += child->getSize();
    }
    return totalSize;
}

void Directory::addChild(std::shared_ptr<FileSystemComponent> child) {
    if (!child || hasChild(child->getName())) {
        return;
    }
    
    children.push_back(child);
    rebuildIndex();
    updateModificationTime();
}

bool Directory::removeChild(const std::string &name) {
    auto it = std::find_if(children.begin(), children.end(),
        [&name](const std::shared_ptr<FileSystemComponent> &child) {
            return child->getName() == name;
        });
    
    if (it != children.end()) {
        children.erase(it);
        rebuildIndex();
        updateModificationTime();
        return true;
    }
    
    return false;
}

std::shared_ptr<FileSystemComponent> Directory::getChild(const std::string &name) const {
    auto it = childIndex.find(name);
    if (it != childIndex.end() && it->second < children.size()) {
        return children[it->second];
    }
    return nullptr;
}

bool Directory::hasChild(const std::string &name) const {
    return childIndex.find(name) != childIndex.end();
}

void Directory::setName(const std::string &name) {
    this->name = name;
    updateModificationTime();
}

void Directory::updateModificationTime() {
    modificationTime = std::time(nullptr);
}

std::vector<std::shared_ptr<FileSystemComponent>> Directory::findByName(const std::string &name) const {
    std::vector<std::shared_ptr<FileSystemComponent>> results;
    
    for (const auto &child : children) {
        if (child->getName().find(name) != std::string::npos) {
            results.push_back(child);
        }
        
        if (child->isDirectory()) {
            auto dir = std::dynamic_pointer_cast<Directory>(child);
            if (dir) {
                auto subResults = dir->findByName(name);
                results.insert(results.end(), subResults.begin(), subResults.end());
            }
        }
    }
    
    return results;
}

std::vector<std::shared_ptr<FileSystemComponent>> Directory::findBySize(std::size_t minSize, std::size_t maxSize) const {
    std::vector<std::shared_ptr<FileSystemComponent>> results;
    
    for (const auto &child : children) {
        std::size_t size = child->getSize();
        if (size >= minSize && size <= maxSize) {
            results.push_back(child);
        }
        
        if (child->isDirectory()) {
            auto dir = std::dynamic_pointer_cast<Directory>(child);
            if (dir) {
                auto subResults = dir->findBySize(minSize, maxSize);
                results.insert(results.end(), subResults.begin(), subResults.end());
            }
        }
    }
    
    return results;
}

std::vector<std::shared_ptr<FileSystemComponent>> Directory::findByTimestamp(std::time_t start, std::time_t end) const {
    std::vector<std::shared_ptr<FileSystemComponent>> results;
    
    for (const auto &child : children) {
        std::time_t modTime = child->getModificationTime();
        if (modTime >= start && modTime <= end) {
            results.push_back(child);
        }
        
        if (child->isDirectory()) {
            auto dir = std::dynamic_pointer_cast<Directory>(child);
            if (dir) {
                auto subResults = dir->findByTimestamp(start, end);
                results.insert(results.end(), subResults.begin(), subResults.end());
            }
        }
    }
    
    return results;
}

void Directory::rebuildIndex() {
    childIndex.clear();
    for (std::size_t i = 0; i < children.size(); ++i) {
        childIndex[children[i]->getName()] = i;
    }
}