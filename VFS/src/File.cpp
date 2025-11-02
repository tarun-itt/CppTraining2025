#include <ctime>
#include <sstream>

#include "../inc/File.h"

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