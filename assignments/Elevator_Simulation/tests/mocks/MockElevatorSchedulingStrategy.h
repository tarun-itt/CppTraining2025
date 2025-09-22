#ifndef MOCK_ELEVATOR_SCHEDULING_STRATEGY_H
#define MOCK_ELEVATOR_SCHEDULING_STRATEGY_H

#include <gmock/gmock.h>

#include "IElevatorSchedulingStrategy.h"

class MockElevatorSchedulingStrategy : public IElevatorSchedulingStrategy {
public:
    MOCK_METHOD(int, findNextStop, (int currentFloor, Direction committedDirection, const std::set<int>& upStops, const std::set<int>& downStops), (const, override));
};

#endif