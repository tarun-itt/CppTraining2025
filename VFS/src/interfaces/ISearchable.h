#pragma once

#include <ctime>
#include <memory>
#include <string>
#include <vector>

#include "FileSystemNode.h"

class ISearchable {
public:
    virtual ~ISearchable() = default;

    virtual std::vector<std::shared_ptr<FileSystemNode>> findByName(const std::string &name) const = 0;
    virtual std::vector<std::shared_ptr<FileSystemNode>> findBySize(size_t minSize, size_t maxSize) const = 0;
    virtual std::vector<std::shared_ptr<FileSystemNode>> findByTimestamp(time_t start, time_t end) const = 0;
};