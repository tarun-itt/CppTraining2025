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

  std::shared_ptr<FileSystemComponent>
  getFileSystemComponent(const std::string &path) const;
  std::shared_ptr<File> getFile(const std::string &path) const;
  std::shared_ptr<Directory> getDirectory(const std::string &path) const;

  std::string getCurrentPath() const;
  std::shared_ptr<Directory> getCurrentDirectory() const;
  std::vector<std::shared_ptr<FileSystemComponent>>
  listCurrentDirectory() const;

  std::string readFile(const std::string &path) const;
  bool writeFile(const std::string &path, const std::string &content);
  bool appendToFile(const std::string &path, const std::string &content);

private:
  std::unique_ptr<FileSystemPersistence> fileSystemStateStorage;
  std::shared_ptr<Directory> root;
  std::shared_ptr<Directory> currentDirectory;
  std::vector<std::string> currentPathComponents;

  std::vector<std::string> splitPathToComponents(const std::string &path) const;
  std::string joinPath(const std::vector<std::string> &pathComponents) const;
  std::shared_ptr<Directory> resolveParentDirectory(const std::string &path,
                                                    std::string &outName) const;
};