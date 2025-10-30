#pragma once

#include <memory>
#include <string>

class FileSystemNode;

class IPersistenceStrategy {
public:
    virtual ~IPersistenceStrategy() = default;

    virtual void saveFileSystem(const std::shared_ptr<FileSystemNode> &root) = 0;
    virtual std::shared_ptr<FileSystemNode> loadFileSystem() = 0;
    virtual bool exists() const = 0;
};