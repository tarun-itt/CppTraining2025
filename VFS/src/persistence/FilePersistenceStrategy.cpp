#include <cstring>
#include <fstream>
#include <memory>

#include "Directory.h"
#include "File.h"
#include "FilePersistenceStrategy.h"
#include "FileSystemObject.h"
#include "IOutputHandler.h"

FilePersistenceStrategy::FilePersistenceStrategy(const std::string &filename, IOutputHandler &output)
    : filename(filename), output(output) {}

void FilePersistenceStrategy::saveFileSystem(const std::shared_ptr<FileSystemObject> &root) {
    try {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            output.writeError("Failed to open file for saving: " + filename);
            return;
        }

        uint32_t version = 1;
        file.write(reinterpret_cast<const char *>(&version), sizeof(version));

        serializeObject(root, file);
        file.close();
    } catch (const std::exception &e) {
        output.writeError("Error saving file system: " + std::string(e.what()));
    }
}

std::shared_ptr<FileSystemObject> FilePersistenceStrategy::loadFileSystem() {
    try {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            return std::make_shared<Directory>("root");
        }

        uint32_t version;
        file.read(reinterpret_cast<char *>(&version), sizeof(version));
        if (file.gcount() != sizeof(version) || version != 1) {
            output.writeError("Invalid file format");
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

void FilePersistenceStrategy::serializeObject(const std::shared_ptr<FileSystemObject> &obj,
                                              std::ostream &stream) const {
    if (!obj) {
        uint8_t type = 0;
        stream.write(reinterpret_cast<const char *>(&type), sizeof(type));
        return;
    }

    if (obj->isFile()) {
        uint8_t type = 1;
        stream.write(reinterpret_cast<const char *>(&type), sizeof(type));

        auto file = std::dynamic_pointer_cast<File>(obj);
        writeString(stream, file->getName());
        writeTime(stream, file->getCreationTime());
        writeTime(stream, file->getModificationTime());
        writeString(stream, file->getContent());
    } else {
        uint8_t type = 2;
        stream.write(reinterpret_cast<const char *>(&type), sizeof(type));

        auto dir = std::dynamic_pointer_cast<Directory>(obj);
        writeString(stream, dir->getName());
        writeTime(stream, dir->getCreationTime());
        writeTime(stream, dir->getModificationTime());

        uint32_t childCount = static_cast<uint32_t>(dir->getChildren().size());
        stream.write(reinterpret_cast<const char *>(&childCount), sizeof(childCount));

        for (const auto &child : dir->getChildren()) {
            serializeObject(child, stream);
        }
    }
}

std::shared_ptr<FileSystemObject> FilePersistenceStrategy::deserializeObject(std::istream &stream) const {
    uint8_t type;
    stream.read(reinterpret_cast<char *>(&type), sizeof(type));

    if (stream.gcount() != sizeof(type)) {
        return nullptr;
    }

    if (type == 0) {
        return nullptr;
    } else if (type == 1) {
        std::string name = readString(stream);
        time_t creationTime = readTime(stream);
        time_t modificationTime = readTime(stream);
        std::string content = readString(stream);

        auto file = std::make_shared<File>(name, content);
        return file;
    } else if (type == 2) {
        std::string name = readString(stream);
        time_t creationTime = readTime(stream);
        time_t modificationTime = readTime(stream);
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
    int64_t timeValue = static_cast<int64_t>(time);
    stream.write(reinterpret_cast<const char *>(&timeValue), sizeof(timeValue));
}

time_t FilePersistenceStrategy::readTime(std::istream &stream) const {
    int64_t timeValue;
    stream.read(reinterpret_cast<char *>(&timeValue), sizeof(timeValue));
    return static_cast<time_t>(timeValue);
}
