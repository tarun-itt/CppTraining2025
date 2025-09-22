#ifndef MOCK_ELEVATOR_ASSIGNMENT_STRATEGY_H
#define MOCK_ELEVATOR_ASSIGNMENT_STRATEGY_H

#include <gmock/gmock.h>

#include "IElevatorAssignmentStrategy.h"

class MockElevatorAssignmentStrategy : public IElevatorAssignmentStrategy {
public:
    MOCK_METHOD(Elevator*, selectElevator, (const InputRequest& request, const std::vector<Elevator*>& availableElevators), (override));
};

#endif