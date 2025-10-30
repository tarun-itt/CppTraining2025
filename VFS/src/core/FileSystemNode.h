#pragma once

#include <ctime>
#include <memory>
#include <string>

enum class NodeType : uint8_t {
    Null = 0,
    File = 1,
    Directory = 2
};

class FileSystemNode {
  public:
    explicit FileSystemNode(const std::string &name);
    virtual ~FileSystemNode() = default;

    virtual bool isFile() const = 0;
    virtual bool isDirectory() const = 0;
    virtual size_t getSize() const = 0;
    virtual NodeType getNodeType() const = 0;

    const std::string &getName() const { return name; }
    time_t getCreationTime() const { return creationTime; }
    time_t getModificationTime() const { return modificationTime; }

    void setName(const std::string &name) {
        this->name = name;
        updateModificationTime();
    }
    void updateModificationTime() { modificationTime = std::time(nullptr); }

  protected:
    std::string name;
    time_t creationTime;
    time_t modificationTime;
};
