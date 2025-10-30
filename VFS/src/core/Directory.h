#pragma once

#include <ctime>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "FileSystemNode.h"
#include "ISearchable.h"

class Directory : public FileSystemNode, public ISearchable {
  public:
    explicit Directory(const std::string &name);

    bool isFile() const override { return false; }
    bool isDirectory() const override { return true; }
    size_t getSize() const override;
    NodeType getNodeType() const override { return NodeType::Directory; }

    void addChild(std::shared_ptr<FileSystemNode> child);
    bool removeChild(const std::string &name);
    std::shared_ptr<FileSystemNode> getChild(const std::string &name) const;
    const std::vector<std::shared_ptr<FileSystemNode>> &getChildren() const { return children; }
    bool hasChild(const std::string &name) const;

    std::vector<std::shared_ptr<FileSystemNode>> findByName(const std::string &name) const override;
    std::vector<std::shared_ptr<FileSystemNode>> findBySize(size_t minSize, size_t maxSize) const override;
    std::vector<std::shared_ptr<FileSystemNode>> findByTimestamp(time_t start, time_t end) const override;

  private:
    std::vector<std::shared_ptr<FileSystemNode>> children;
    std::unordered_map<std::string, size_t> childIndex;

    void rebuildIndex();
};