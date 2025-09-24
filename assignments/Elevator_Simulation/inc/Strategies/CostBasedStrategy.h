#ifndef COST_BASED_ELEVATOR_SELECTION_H
#define COST_BASED_ELEVATOR_SELECTION_H

#include <vector>

#include "Interfaces/IElevatorAssignmentStrategy.h"
#include "Core/Elevator.h"
#include "Input/InputRequest.h"
#include "Display/MessageSender.h"

class CostBasedStrategy : public IElevatorAssignmentStrategy {

    public:
        CostBasedStrategy(MessageSender* messageSender = nullptr);
        Elevator* selectElevator(const InputRequest& request, const std::vector<Elevator*>& availableElevators) override;

    private:
        static const int FloorTravelCost = 1;
        static const int StopCost = 3;

        int calculateCost(const Elevator* elevator, const InputRequest& request);
        
        MessageSender* messageSender;
};

#endif