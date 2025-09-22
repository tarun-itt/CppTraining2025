#ifndef I_ELEVATOR_ASSIGNMENT_STRATEGY_H
#define I_ELEVATOR_ASSIGNMENT_STRATEGY_H

#include <vector>
#include <string>

#include "Elevator.h"
#include "InputRequest.h"

class IElevatorAssignmentStrategy {
public:
    virtual ~IElevatorAssignmentStrategy() = default;

    virtual Elevator* selectElevator(const InputRequest& request, const std::vector<Elevator*>& availableElevators) = 0;
};

#endif