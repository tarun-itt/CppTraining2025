#ifndef MOCKLANE_H
#define MOCKLANE_H

#include <gmock/gmock.h>
#include <string>
#include "ILane.h"

class MockLane : public ILane {
public:
    MOCK_METHOD(const std::string&, getName, (), (const, override));
    MOCK_METHOD(bool, hasCars, (), (const, override));
    MOCK_METHOD(bool, processCar, (), (override));
    MOCK_METHOD(int, getRemainingCarCount, (), (const, override));
    MOCK_METHOD(int, getInitialCarCount, (), (const, override));
};

#endif