#ifndef IINPUT_READER_H
#define IINPUT_READER_H

#include <functional>

#include "InputRequest.h"

class IInputReader {
public:
    virtual ~IInputReader() = default;
    
    virtual void start() = 0;    
    virtual void stop() = 0;    
    virtual void setRequestCallback(std::function<void(const InputRequest&)> callback) = 0;    
    virtual bool isRunning() const = 0;
};

#endif