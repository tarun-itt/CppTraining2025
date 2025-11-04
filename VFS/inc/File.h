#pragma once

#include <ctime>
#include <memory>
#include <string>
#include <vector>

#include "FileSystemComponent.h"

class File : public FileSystemComponent {
public:
  explicit File(const std::string &name, const std::string &content = "");

  std::string getName() const override;
  std::time_t getCreationTime() const override;
  std::time_t getModificationTime() const override;
  std::size_t getSize() const override;
  FileSystemComponentType getComponentType() const override;

  bool isFile() const override;
  bool isDirectory() const override;

  const std::string &getContent() const;
  void setContent(const std::string &content);
  void appendContent(const std::string &content);

  std::vector<std::shared_ptr<FileSystemComponent>>
  findByContent(const std::string &pattern) const;
  std::vector<std::string> searchLines(const std::string &pattern) const;

  void setName(const std::string &name);
  void updateModificationTime();

private:
  std::string name;
  std::time_t creationTime;
  std::time_t modificationTime;
  std::string content;
};