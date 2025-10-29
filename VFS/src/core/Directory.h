#pragma once

#include <ctime>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "FileSystemObject.h"
#include "ISearchable.h"

class Directory : public FileSystemObject, public ISearchable {
  public:
    explicit Directory(const std::string &name);

    bool isFile() const override { return false; }
    bool isDirectory() const override { return true; }
    size_t getSize() const override;

    void addChild(std::shared_ptr<FileSystemObject> child);
    bool removeChild(const std::string &name);
    std::shared_ptr<FileSystemObject> getChild(const std::string &name) const;
    const std::vector<std::shared_ptr<FileSystemObject>> &getChildren() const { return children; }
    bool hasChild(const std::string &name) const;

    std::vector<std::shared_ptr<FileSystemObject>> findByName(const std::string &name) const override;
    std::vector<std::shared_ptr<FileSystemObject>> findBySize(size_t minSize, size_t maxSize) const override;
    std::vector<std::shared_ptr<FileSystemObject>> findByTimestamp(time_t start, time_t end) const override;

  private:
    std::vector<std::shared_ptr<FileSystemObject>> children;
    std::unordered_map<std::string, size_t> childIndex;

    void rebuildIndex();
};