#ifndef MOCK_BLOCKING_QUEUE_H
#define MOCK_BLOCKING_QUEUE_H

#include <gmock/gmock.h>

#include "IBlockingQueue.h"

template<typename T>
class MockBlockingQueue : public IBlockingQueue<T> {
public:
    MOCK_METHOD(void, push, (const T& item), (override));
    MOCK_METHOD(T, try_pop, (), (override));
    MOCK_METHOD(bool, empty, (), (const, override));
    MOCK_METHOD(size_t, size, (), (const, override));
    MOCK_METHOD(void, shutdown, (), (override));
};

#endif