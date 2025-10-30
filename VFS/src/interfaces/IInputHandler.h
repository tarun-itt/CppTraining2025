#pragma once

#include <string>

class IInputHandler {
public:
    virtual ~IInputHandler() = default;

    virtual std::string readLine() = 0;
    virtual bool canReadInput() const = 0;
    virtual void setEndOfInput() = 0;
};