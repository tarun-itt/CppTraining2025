#ifndef IBLOCKING_QUEUE_H
#define IBLOCKING_QUEUE_H

#include "Input/InputRequest.h"
#include <memory>

template<typename T>
class IBlockingQueue {
public:
    virtual ~IBlockingQueue() = default;
    
    virtual void push(const T& item) = 0;
    virtual T try_pop() = 0;
    virtual bool empty() const = 0;
    virtual size_t size() const = 0;
    virtual void shutdown() = 0;
};

#endif