#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

#include "Directory.h"
#include "File.h"
#include "FileSystem.h"
#include "FileSystemPersistence.h"

namespace {
constexpr const char *DIRECTORY_PREFIX = "DIR:";
constexpr const char *FILE_PREFIX = "FILE:";
constexpr const char *CONTENT_PREFIX = "CONTENT:";
constexpr const char *END_FILE_MARKER = "END_FILE";

bool startsWith(const std::string &str, const std::string &prefix) {
  return str.size() >= prefix.size() &&
         str.compare(0, prefix.size(), prefix) == 0;
}

std::string extractAfterPrefix(const std::string &line,
                               const std::string &prefix) {
  return line.substr(prefix.size());
}

std::string readFileContent(std::ifstream &in, size_t contentSize) {
  std::string content(contentSize, '\0');
  in.read(&content[0], contentSize);

  std::string endMarker;
  std::getline(in, endMarker);

  return content;
}

void saveDirectory(std::ofstream &out, const std::shared_ptr<Directory> &dir,
                   const std::string &path) {
  auto children = dir->getChildren();

  for (const auto &child : children) {
    std::string childPath =
        (path == "/") ? "/" + child->getName() : path + "/" + child->getName();

    if (child->isDirectory()) {
      out << DIRECTORY_PREFIX << childPath << '\n';
      auto childDir = std::dynamic_pointer_cast<Directory>(child);
      saveDirectory(out, childDir, childPath);
    } else {
      auto filePtr = std::dynamic_pointer_cast<File>(child);

      out << FILE_PREFIX << childPath << '\n';
      out << CONTENT_PREFIX << filePtr->getContent().size() << '\n';
      out << filePtr->getContent();
      out << END_FILE_MARKER << '\n';
    }
  }
}
} // namespace

FileSystemPersistence::FileSystemPersistence(const std::string &filename)
    : filename(filename) {}

void FileSystemPersistence::saveFileSystem(const FileSystem &fs) {
  std::ofstream out(filename);
  if (!out) {
    std::cerr << "Error: Could not save file system to " << filename << '\n';
    return;
  }

  if (auto rootDir = fs.getDirectory("/")) {
    saveDirectory(out, rootDir, "/");
  }
}

void FileSystemPersistence::loadFileSystem(FileSystem &fs) {
  std::ifstream in(filename);
  if (!in) {
    return;
  }

  std::string line;
  std::string currentPath = "/";

  while (std::getline(in, line)) {
    if (line.empty())
      continue;

    if (startsWith(line, DIRECTORY_PREFIX)) {
      std::string dirPath = extractAfterPrefix(line, DIRECTORY_PREFIX);
      fs.createDirectory(dirPath);
    } else if (startsWith(line, FILE_PREFIX)) {
      std::string filePath = extractAfterPrefix(line, FILE_PREFIX);

      std::getline(in, line);
      if (!startsWith(line, CONTENT_PREFIX))
        continue;

      size_t contentSize =
          std::stoull(extractAfterPrefix(line, CONTENT_PREFIX));
      std::string content = readFileContent(in, contentSize);

      fs.createFile(filePath, content);
    }
  }

  if (currentPath != "/") {
    fs.changeDir(currentPath);
  }
}
