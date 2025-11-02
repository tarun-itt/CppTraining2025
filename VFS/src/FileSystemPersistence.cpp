#include <fstream>
#include <iostream>
#include <cstring>

#include "../inc/FileSystemPersistence.h"
#include "../inc/FileSystem.h"
#include "../inc/Directory.h"
#include "../inc/File.h"

namespace {
    constexpr const char* CURRENT_PATH_PREFIX = "CURRENT_PATH:";
    constexpr const char* DIRECTORY_PREFIX = "DIR:";
    constexpr const char* FILE_PREFIX = "FILE:";
    constexpr const char* END_MARKER = "<<END_FILE>>";
}

class FilePersistence : public FileSystemPersistence {
private:
    std::string filename;

    void serializeDirectory(std::ofstream &file, const std::shared_ptr<Directory> &dir, const std::string &path) {
        auto children = dir->getChildren();
        for (const auto &child : children) {
            std::string childPath = (path == "/") ? "/" + child->getName() : path + "/" + child->getName();

            if (child->isDirectory()) {
                file << DIRECTORY_PREFIX << childPath << std::endl;
                auto childDir = std::dynamic_pointer_cast<Directory>(child);
                serializeDirectory(file, childDir, childPath);
            } else {
                auto filePtr = std::dynamic_pointer_cast<File>(child);
                file << FILE_PREFIX << childPath << std::endl;
                file << filePtr->getContent();
                if (!filePtr->getContent().empty() && filePtr->getContent().back() != '\n') {
                    file << std::endl;
                }
            }
        }
    }

public:
    explicit FilePersistence(const std::string &filename) : filename(filename) {}

    void saveFileSystem(const FileSystem &fs) override {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Warning: Could not save file system data" << std::endl;
            return;
        }

        file << CURRENT_PATH_PREFIX << fs.getCurrentPath() << std::endl;

        auto rootDir = fs.getDirectory("/");
        if (rootDir) {
            serializeDirectory(file, rootDir, "/");
        }

        file.close();
    }

    void loadFileSystem(FileSystem &fs) override {
        std::ifstream file(filename);
        if (!file.is_open()) {
            return;
        }

        std::string line;
        std::string currentPath = "/";

        while (std::getline(file, line)) {
            if (line.empty()) continue;

            if (line.substr(0, strlen(CURRENT_PATH_PREFIX)) == CURRENT_PATH_PREFIX) {
                currentPath = line.substr(strlen(CURRENT_PATH_PREFIX));
            } else if (line.substr(0, strlen(DIRECTORY_PREFIX)) == DIRECTORY_PREFIX) {
                std::string dirPath = line.substr(strlen(DIRECTORY_PREFIX));
                fs.createDirectory(dirPath);
            } else if (line.substr(0, strlen(FILE_PREFIX)) == FILE_PREFIX) {
                std::string filePath = line.substr(strlen(FILE_PREFIX));
                
                std::string content;
                std::streampos currentPos = file.tellg();
                std::string contentLine;
                
                while (std::getline(file, contentLine)) {
                    if (contentLine.substr(0, strlen(DIRECTORY_PREFIX)) == DIRECTORY_PREFIX || 
                        contentLine.substr(0, strlen(FILE_PREFIX)) == FILE_PREFIX || 
                        contentLine.substr(0, strlen(CURRENT_PATH_PREFIX)) == CURRENT_PATH_PREFIX) {
                        file.seekg(currentPos);
                        break;
                    }
                    
                    if (contentLine == END_MARKER) {
                        break;
                    }
                    
                    if (contentLine.length() >= strlen(END_MARKER) && 
                        contentLine.substr(contentLine.length() - strlen(END_MARKER)) == END_MARKER) {
                        contentLine = contentLine.substr(0, contentLine.length() - strlen(END_MARKER));
                        if (!content.empty()) {
                            content += "\n";
                        }
                        content += contentLine;
                        break;
                    }
                    
                    if (!content.empty()) {
                        content += "\n";
                    }
                    content += contentLine;
                    currentPos = file.tellg();
                }
                
                fs.createFile(filePath, content);
            }
        }

        file.close();

        if (currentPath != "/") {
            fs.changeDir(currentPath);
        }
    }

    void serialize() override {}
    void deserialize() override {}
};

std::unique_ptr<FileSystemPersistence> createFilePersistence(const std::string &filename) {
    return std::make_unique<FilePersistence>(filename);
}