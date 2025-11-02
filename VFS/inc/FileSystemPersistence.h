#pragma once

#include <string>
#include <memory>

class FileSystem;

class FileSystemPersistence {
public:
    virtual ~FileSystemPersistence() = default;

    virtual void saveFileSystem(const FileSystem &fs) = 0;
    virtual void loadFileSystem(FileSystem &fs) = 0;
    virtual void serialize() = 0;
    virtual void deserialize() = 0;
};

std::unique_ptr<FileSystemPersistence> createFilePersistence(const std::string &filename);