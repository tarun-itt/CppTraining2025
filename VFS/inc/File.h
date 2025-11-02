#pragma once

#include <memory>
#include <string>
#include <vector>
#include <ctime>

#include "FileSystemComponent.h"

class File : public FileSystemComponent {
public:
    explicit File(const std::string &name, const std::string &content = "");

    std::string getName() const override { return name; }
    std::time_t getCreationTime() const override { return creationTime; }
    std::time_t getModificationTime() const override { return modificationTime; }
    std::size_t getSize() const override { return content.size(); }
    FileSystemComponentType getComponentType() const override { return FileSystemComponentType::File; }

    bool isFile() const override { return true; }
    bool isDirectory() const override { return false; }

    const std::string &getContent() const { return content; }
    void setContent(const std::string &content);
    void appendContent(const std::string &content);

    std::vector<std::shared_ptr<FileSystemComponent>> findByContent(const std::string &pattern) const;
    std::vector<std::string> searchLines(const std::string &pattern) const;

    void setName(const std::string &name);
    void updateModificationTime();

private:
    std::string name;
    std::time_t creationTime;
    std::time_t modificationTime;
    std::string content;
};