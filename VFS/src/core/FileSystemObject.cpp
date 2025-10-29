#include <ctime>

#include "FileSystemObject.h"

FileSystemObject::FileSystemObject(const std::string &name)
    : name(name), creationTime(std::time(nullptr)), modificationTime(std::time(nullptr)) {}
