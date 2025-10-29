#pragma once

#include <string>

class IInputHandler {
public:
    virtual ~IInputHandler() = default;

    virtual std::string readLine(const std::string &prompt = "") = 0;
    virtual bool hasInput() const = 0;
    virtual void setEndOfInput() = 0;
};