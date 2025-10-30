#include <ctime>

#include "FileSystemNode.h"

FileSystemNode::FileSystemNode(const std::string &name)
    : name(name), creationTime(std::time(nullptr)), modificationTime(std::time(nullptr)) {}
