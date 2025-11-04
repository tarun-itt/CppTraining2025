#pragma once

#include <string>

class FileSystem;

class FileSystemPersistence {
public:
    explicit FileSystemPersistence(const std::string &filename);
    ~FileSystemPersistence() = default;

    void saveFileSystem(const FileSystem &fs);
    void loadFileSystem(FileSystem &fs);

private:
    std::string filename;
};