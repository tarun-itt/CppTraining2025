#ifndef COST_BASED_ELEVATOR_SELECTION_H
#define COST_BASED_ELEVATOR_SELECTION_H

#include <vector>

#include "IElevatorAssignmentStrategy.h"
#include "Elevator.h"
#include "InputRequest.h"
#include "MessageSender.h"

class CostBasedStrategy : public IElevatorAssignmentStrategy {

    public:
        CostBasedStrategy(MessageSender* messageSender = nullptr);
        Elevator* selectElevator(const InputRequest& request, const std::vector<Elevator*>& availableElevators) override;

    private:
        static const int FLOOR_TRAVEL_COST = 1;
        static const int STOP_COST = 3;

        int calculateCost(const Elevator* elevator, const InputRequest& request);
        
        MessageSender* messageSender;
};

#endif