#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Directory.h"
#include "File.h"
#include "IContentSearchable.h"
#include "IPersistenceStrategy.h"
#include "ISearchable.h"

class FileSystemManager : public ISearchable, public IContentSearchable {
  public:
    explicit FileSystemManager(std::unique_ptr<IPersistenceStrategy> persistence);
    ~FileSystemManager();

    void initialize();
    void save();
    void load();

    bool createDirectory(const std::string &path);
    bool createFile(const std::string &path, const std::string &content = "");
    bool remove(const std::string &path);
    bool changeDirectory(const std::string &path);
    bool exists(const std::string &path) const;

    std::shared_ptr<FileSystemNode> getObject(const std::string &path) const;
    std::shared_ptr<File> getFile(const std::string &path) const;
    std::shared_ptr<Directory> getDirectory(const std::string &path) const;

    std::string getCurrentPath() const;
    std::shared_ptr<Directory> getCurrentDirectory() const { return currentDirectory; }
    std::vector<std::shared_ptr<FileSystemNode>> listCurrentDirectory() const;

    std::string readFile(const std::string &path) const;
    bool writeFile(const std::string &path, const std::string &content);
    bool appendToFile(const std::string &path, const std::string &content);

    std::vector<std::shared_ptr<FileSystemNode>> findByName(const std::string &name) const override;
    std::vector<std::shared_ptr<FileSystemNode>> findBySize(size_t minSize, size_t maxSize) const override;
    std::vector<std::shared_ptr<FileSystemNode>> findByTimestamp(time_t start, time_t end) const override;
    std::vector<std::shared_ptr<FileSystemNode>> findByContent(const std::string &pattern) const override;
    std::vector<std::string> searchLines(const std::string &pattern) const override;

  private:
    std::unique_ptr<IPersistenceStrategy> persistence;
    std::shared_ptr<Directory> root;
    std::shared_ptr<Directory> currentDirectory;
    std::vector<std::string> currentPath;

    std::shared_ptr<FileSystemNode> navigateToPath(const std::string &path) const;
    std::vector<std::string> splitPath(const std::string &path) const;
    std::string joinPath(const std::vector<std::string> &pathComponents) const;
    bool isAbsolutePath(const std::string &path) const;
    void collectContentSearchableObjects(const std::shared_ptr<FileSystemNode> &obj,
                                         std::vector<std::shared_ptr<FileSystemNode>> &results,
                                         const std::string &pattern) const;
};