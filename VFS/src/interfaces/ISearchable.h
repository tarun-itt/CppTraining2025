#pragma once

#include <ctime>
#include <memory>
#include <string>
#include <vector>

#include "FileSystemObject.h"

class ISearchable {
public:
    virtual ~ISearchable() = default;

    virtual std::vector<std::shared_ptr<FileSystemObject>> findByName(const std::string &name) const = 0;
    virtual std::vector<std::shared_ptr<FileSystemObject>> findBySize(size_t minSize, size_t maxSize) const = 0;
    virtual std::vector<std::shared_ptr<FileSystemObject>> findByTimestamp(time_t start, time_t end) const = 0;
};