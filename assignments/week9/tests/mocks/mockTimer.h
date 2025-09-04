#ifndef MOCKTIMER_H
#define MOCKTIMER_H

#include <gmock/gmock.h>
#include "ITimer.h"

class MockTimer : public ITimer {
public:
    MOCK_METHOD(void, sleep, (int seconds), (override));
};

#endif