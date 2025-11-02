#pragma once

#include <ctime>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "FileSystemComponent.h"

class Directory : public FileSystemComponent {
public:
    explicit Directory(const std::string &name);

    std::string getName() const override { return name; }
    std::time_t getCreationTime() const override { return creationTime; }
    std::time_t getModificationTime() const override { return modificationTime; }
    std::size_t getSize() const override;
    FileSystemComponentType getComponentType() const override { return FileSystemComponentType::Directory; }

    bool isFile() const override { return false; }
    bool isDirectory() const override { return true; }

    void addChild(std::shared_ptr<FileSystemComponent> child);
    bool removeChild(const std::string &name);
    std::shared_ptr<FileSystemComponent> getChild(const std::string &name) const;
    const std::vector<std::shared_ptr<FileSystemComponent>> &getChildren() const { return children; }
    bool hasChild(const std::string &name) const;

    std::vector<std::shared_ptr<FileSystemComponent>> findByName(const std::string &name) const;
    std::vector<std::shared_ptr<FileSystemComponent>> findBySize(std::size_t minSize, std::size_t maxSize) const;
    std::vector<std::shared_ptr<FileSystemComponent>> findByTimestamp(std::time_t start, std::time_t end) const;

    void setName(const std::string &name);
    void updateModificationTime();

private:
    std::string name;
    std::time_t creationTime;
    std::time_t modificationTime;
    std::vector<std::shared_ptr<FileSystemComponent>> children;
    std::unordered_map<std::string, std::size_t> childIndex;

    void rebuildIndex();
};