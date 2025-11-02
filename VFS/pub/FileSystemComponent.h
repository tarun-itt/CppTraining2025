#pragma once

#include <ctime>
#include <memory>
#include <string>

enum class FileSystemComponentType : uint8_t {
    File = 0,
    Directory = 1
};

class FileSystemComponent {
public:
    virtual ~FileSystemComponent() = default;

    virtual std::string getName() const = 0;
    virtual std::time_t getCreationTime() const = 0;
    virtual std::time_t getModificationTime() const = 0;
    virtual std::size_t getSize() const = 0;
    virtual FileSystemComponentType getComponentType() const = 0;

    virtual bool isFile() const = 0;
    virtual bool isDirectory() const = 0;
};