#pragma once

#include <memory>
#include <string>

class FileSystemObject;

class IPersistenceStrategy {
public:
    virtual ~IPersistenceStrategy() = default;

    virtual void saveFileSystem(const std::shared_ptr<FileSystemObject> &root) = 0;
    virtual std::shared_ptr<FileSystemObject> loadFileSystem() = 0;
    virtual bool exists() const = 0;
};