#pragma once

#include <memory>
#include <string>

#include "FileSystemObject.h"
#include "IContentSearchable.h"

class File : public FileSystemObject, public IContentSearchable {
  public:
    explicit File(const std::string &name, const std::string &content = "");

    bool isFile() const override { return true; }
    bool isDirectory() const override { return false; }
    size_t getSize() const override { return content.size(); }

    const std::string &getContent() const { return content; }
    void setContent(const std::string &content);
    void appendContent(const std::string &content);

    std::vector<std::shared_ptr<FileSystemObject>> findByContent(const std::string &pattern) const override;
    std::vector<std::string> searchLines(const std::string &pattern) const override;

  private:
    std::string content;
};