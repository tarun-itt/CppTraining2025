#include <algorithm>
#include <sstream>

#include "File.h"
#include "FileSystemObject.h"

File::File(const std::string &name, const std::string &content) : FileSystemObject(name), content(content) {}

void File::setContent(const std::string &content) {
    this->content = content;
    updateModificationTime();
}

void File::appendContent(const std::string &content) {
    this->content += content;
    updateModificationTime();
}

std::vector<std::shared_ptr<FileSystemObject>> File::findByContent(const std::string &pattern) const {
    std::vector<std::shared_ptr<FileSystemObject>> result;
    if (content.find(pattern) != std::string::npos) {
        result.push_back(std::make_shared<File>(*this));
    }
    return result;
}

std::vector<std::string> File::searchLines(const std::string &pattern) const {
    std::vector<std::string> result;
    std::istringstream stream(content);
    std::string line;

    while (std::getline(stream, line)) {
        if (line.find(pattern) != std::string::npos) {
            result.push_back(line);
        }
    }
    return result;
}
