#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Directory.h"
#include "File.h"
#include "FileSystemComponent.h"

class FileSystemPersistence;

class FileSystem {
public:
    explicit FileSystem(std::unique_ptr<FileSystemPersistence> persistence);
    ~FileSystem();

    void initialize();
    void saveFileSystem();
    void loadFileSystem();

    bool createDirectory(const std::string &path);
    bool createFile(const std::string &path, const std::string &content = "");
    bool removeFile(const std::string &path);
    bool removeDir(const std::string &path);
    bool changeDir(const std::string &path);
    bool exists(const std::string &path) const;

    std::shared_ptr<FileSystemComponent> getObject(const std::string &path) const;
    std::shared_ptr<File> getFile(const std::string &path) const;
    std::shared_ptr<Directory> getDirectory(const std::string &path) const;

    std::string getCurrentPath() const;
    std::shared_ptr<Directory> getCurrentDirectory() const { return currentDirectory; }
    std::vector<std::shared_ptr<FileSystemComponent>> listCurrentDirectory() const;

    std::string readFile(const std::string &path) const;
    bool writeFile(const std::string &path, const std::string &content);
    bool appendToFile(const std::string &path, const std::string &content);

    std::vector<std::shared_ptr<FileSystemComponent>> findByName(const std::string &name) const;
    std::vector<std::shared_ptr<FileSystemComponent>> findBySize(std::size_t minSize, std::size_t maxSize) const;
    std::vector<std::shared_ptr<FileSystemComponent>> findByTimestamp(std::time_t start, std::time_t end) const;
    std::vector<std::shared_ptr<FileSystemComponent>> findByContent(const std::string &pattern) const;
    std::vector<std::string> searchLines(const std::string &pattern) const;

private:
    std::unique_ptr<FileSystemPersistence> persistence;
    std::shared_ptr<Directory> root;
    std::shared_ptr<Directory> currentDirectory;
    std::vector<std::string> currentPath;

    std::vector<std::string> parsePath(const std::string &path) const;
    std::shared_ptr<Directory> navigateToParent(const std::vector<std::string> &pathComponents) const;
    std::string joinPath(const std::vector<std::string> &pathComponents) const;
};