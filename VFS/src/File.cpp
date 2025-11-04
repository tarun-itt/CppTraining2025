#include <ctime>
#include <sstream>

#include "File.h"

File::File(const std::string &name, const std::string &content) 
    : name(name), content(content) {
    creationTime = std::time(nullptr);
    modificationTime = creationTime;
}

void File::setContent(const std::string &content) {
    this->content = content;
    updateModificationTime();
}

void File::appendContent(const std::string &content) {
    this->content += content;
    updateModificationTime();
}

void File::setName(const std::string &name) {
    this->name = name;
    updateModificationTime();
}

void File::updateModificationTime() {
    modificationTime = std::time(nullptr);
}

std::string File::getName() const {
    return name;
}

std::time_t File::getCreationTime() const {
    return creationTime;
}

std::time_t File::getModificationTime() const {
    return modificationTime;
}

std::size_t File::getSize() const {
    return content.size();
}

FileSystemComponentType File::getComponentType() const {
    return FileSystemComponentType::File;
}

bool File::isFile() const {
    return true;
}

bool File::isDirectory() const {
    return false;
}

const std::string &File::getContent() const {
    return content;
}

std::vector<std::shared_ptr<FileSystemComponent>> File::findByContent(const std::string &pattern) const {
    std::vector<std::shared_ptr<FileSystemComponent>> results;
    
    if (content.find(pattern) != std::string::npos) {
    }
    
    return results;
}

std::vector<std::string> File::searchLines(const std::string &pattern) const {
    std::vector<std::string> matchingLines;
    std::istringstream stream(content);
    std::string line;
    
    while (std::getline(stream, line)) {
        if (line.find(pattern) != std::string::npos) {
            matchingLines.push_back(line);
        }
    }
    
    return matchingLines;
}