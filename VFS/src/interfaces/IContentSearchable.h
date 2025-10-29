#pragma once

#include <memory>
#include <string>
#include <vector>

#include "FileSystemObject.h"

class IContentSearchable {
public:
    virtual ~IContentSearchable() = default;

    virtual std::vector<std::shared_ptr<FileSystemObject>> findByContent(const std::string &pattern) const = 0;
    virtual std::vector<std::string> searchLines(const std::string &pattern) const = 0;
};