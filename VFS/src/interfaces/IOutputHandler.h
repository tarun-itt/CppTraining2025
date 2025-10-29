#pragma once

#include <string>

class IOutputHandler {
public:
    virtual ~IOutputHandler() = default;

    virtual void write(const std::string &text) = 0;
    virtual void writeLine(const std::string &text) = 0;
    virtual void writeError(const std::string &error) = 0;
};