#include <cstring>
#include <fstream>
#include <memory>

#include "Directory.h"
#include "File.h"
#include "FilePersistenceStrategy.h"
#include "FileSystemNode.h"
#include "IOutputHandler.h"

FilePersistenceStrategy::FilePersistenceStrategy(const std::string &filename, IOutputHandler &output)
    : filename(filename), output(output) {}

void FilePersistenceStrategy::saveFileSystem(const std::shared_ptr<FileSystemNode> &root) {
    try {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            output.writeError("Failed to open file for saving: " + filename);
            return;
        }

        serializeObject(root, file);
        file.close();
    } catch (const std::exception &e) {
        output.writeError("Error saving file system: " + std::string(e.what()));
    }
}

std::shared_ptr<FileSystemNode> FilePersistenceStrategy::loadFileSystem() {
    try {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            return std::make_shared<Directory>("root");
        }

        auto result = deserializeObject(file);
        file.close();

        if (result) {
            return result;
        } else {
            output.writeError("Failed to deserialize file system");
            return std::make_shared<Directory>("root");
        }
    } catch (const std::exception &e) {
        output.writeError("Error loading file system: " + std::string(e.what()));
        return std::make_shared<Directory>("root");
    }
}

bool FilePersistenceStrategy::exists() const {
    std::ifstream file(filename, std::ios::binary);
    return file.good();
}

void FilePersistenceStrategy::serializeObject(const std::shared_ptr<FileSystemNode> &node,
                                              std::ostream &stream) const {
    if (!node) {
        uint8_t type = static_cast<uint8_t>(NodeType::Null);
        stream.write(reinterpret_cast<const char *>(&type), sizeof(type));
        return;
    }

    uint8_t type = static_cast<uint8_t>(node->getNodeType());
    stream.write(reinterpret_cast<const char *>(&type), sizeof(type));

    writeString(stream, node->getName());
    writeTime(stream, node->getCreationTime());
    writeTime(stream, node->getModificationTime());

    if (node->isFile()) {
        auto file = std::dynamic_pointer_cast<File>(node);
        writeString(stream, file->getContent());
    } else if (node->isDirectory()) {
        auto dir = std::dynamic_pointer_cast<Directory>(node);
        uint32_t childCount = static_cast<uint32_t>(dir->getChildren().size());
        stream.write(reinterpret_cast<const char *>(&childCount), sizeof(childCount));

        for (const auto &child : dir->getChildren()) {
            serializeObject(child, stream);
        }
    }
}

std::shared_ptr<FileSystemNode> FilePersistenceStrategy::deserializeObject(std::istream &stream) const {
    uint8_t type;
    stream.read(reinterpret_cast<char *>(&type), sizeof(type));

    if (stream.gcount() != sizeof(type)) {
        return nullptr;
    }

    NodeType objType = static_cast<NodeType>(type);

    if (objType == NodeType::Null) {
        return nullptr;
    } else if (objType == NodeType::File) {
        std::string name = readString(stream);
        readTime(stream);
        readTime(stream);
        std::string content = readString(stream);

        auto file = std::make_shared<File>(name, content);
        return file;
    } else if (objType == NodeType::Directory) {
        std::string name = readString(stream);
        readTime(stream);
        readTime(stream);
        auto dir = std::make_shared<Directory>(name);

        uint32_t childCount;
        stream.read(reinterpret_cast<char *>(&childCount), sizeof(childCount));

        for (uint32_t i = 0; i < childCount; ++i) {
            auto child = deserializeObject(stream);
            if (child) {
                dir->addChild(child);
            }
        }

        return dir;
    }

    return nullptr;
}

void FilePersistenceStrategy::writeString(std::ostream &stream, const std::string &str) const {
    uint32_t length = static_cast<uint32_t>(str.length());
    stream.write(reinterpret_cast<const char *>(&length), sizeof(length));
    stream.write(str.c_str(), length);
}

std::string FilePersistenceStrategy::readString(std::istream &stream) const {
    uint32_t length;
    stream.read(reinterpret_cast<char *>(&length), sizeof(length));

    if (stream.gcount() != sizeof(length)) {
        return "";
    }

    std::string str(length, '\0');
    stream.read(&str[0], length);

    if (stream.gcount() != static_cast<std::streamsize>(length)) {
        return "";
    }

    return str;
}

void FilePersistenceStrategy::writeTime(std::ostream &stream, time_t time) const {
    int32_t timeValue = static_cast<int32_t>(time);
    stream.write(reinterpret_cast<const char *>(&timeValue), sizeof(timeValue));
}

time_t FilePersistenceStrategy::readTime(std::istream &stream) const {
    int32_t timeValue;
    stream.read(reinterpret_cast<char *>(&timeValue), sizeof(timeValue));
    return static_cast<time_t>(timeValue);
}
