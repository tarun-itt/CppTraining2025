#pragma once

#include <fstream>
#include <memory>
#include <string>

#include "Directory.h"
#include "File.h"
#include "FileSystemObject.h"
#include "IOutputHandler.h"
#include "IPersistenceStrategy.h"

class FilePersistenceStrategy : public IPersistenceStrategy {
  public:
    FilePersistenceStrategy(const std::string &filename, IOutputHandler &output);

    void saveFileSystem(const std::shared_ptr<FileSystemObject> &root) override;
    std::shared_ptr<FileSystemObject> loadFileSystem() override;
    bool exists() const override;

  private:
    std::string filename;
    IOutputHandler &output;

    void serializeObject(const std::shared_ptr<FileSystemObject> &obj, std::ostream &stream) const;
    std::shared_ptr<FileSystemObject> deserializeObject(std::istream &stream) const;
    void writeString(std::ostream &stream, const std::string &str) const;
    std::string readString(std::istream &stream) const;
    void writeTime(std::ostream &stream, time_t time) const;
    time_t readTime(std::istream &stream) const;
};