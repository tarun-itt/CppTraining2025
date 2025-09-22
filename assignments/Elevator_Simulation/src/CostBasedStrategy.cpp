#include <climits>
#include <iostream>
#include <algorithm>

#include "CostBasedStrategy.h"

CostBasedStrategy::CostBasedStrategy(MessageSender* messageSender)
    : messageSender(messageSender) {}

Elevator* CostBasedStrategy::selectElevator(const InputRequest& request,
                                              const std::vector<Elevator*>& availableElevators) {
    Elevator* bestElevator = nullptr;
    int minCost = INT_MAX;


    for (const auto* elevator : availableElevators) {
        int cost = calculateCost(elevator, request);

        if (cost < minCost) {
            minCost = cost;
            bestElevator = const_cast<Elevator*>(elevator);
        }
    }

    if (bestElevator) {
        if (messageSender) {
            messageSender->sendNormal("  >>> Assigning to Elevator " + std::to_string(bestElevator->getSnapshot().id+1));
        }
    } else {
        if (messageSender) {
            messageSender->sendWarning("  >>> No suitable elevator found for the request.");
        }
    }

    return bestElevator;
}

int CostBasedStrategy::calculateCost(const Elevator* elevator, const InputRequest& request) {
    ElevatorSnapshot status = elevator->getSnapshot();
    int pickupFloor = request.requestedAtFloor;
    Direction requestDirection = request.direction;
    
    if (request.targetFloors.empty()) {
        return INT_MAX;
    }

    if (status.state == ElevatorState::IDLE) {
        int baseCost = std::abs(status.currentFloor - pickupFloor) * FLOOR_TRAVEL_COST;
        int targetCost = 0;
        
        for (int target : request.targetFloors) {
            targetCost += std::abs(pickupFloor - target) * FLOOR_TRAVEL_COST;
        }
        
        return baseCost + targetCost + (request.targetFloors.size() * STOP_COST);
    }

    if (status.committedDirection == requestDirection || requestDirection == Direction::IDLE) {
        if ((requestDirection == Direction::UP && status.currentFloor > pickupFloor) ||
            (requestDirection == Direction::DOWN && status.currentFloor < pickupFloor)) {
            return INT_MAX;
        }

        int travelCost = std::abs(status.currentFloor - pickupFloor) * FLOOR_TRAVEL_COST;
        int stopCost = 0;
        
        auto stops = (requestDirection == Direction::UP) ? elevator->getUpStops() : elevator->getDownStops();
        for (int stop : stops) {
            if ((requestDirection == Direction::UP && stop > status.currentFloor && stop < pickupFloor) ||
                (requestDirection == Direction::DOWN && stop < status.currentFloor && stop > pickupFloor)) {
                stopCost += STOP_COST;
            }
        }
        
        int targetCost = 0;
        for (int target : request.targetFloors) {
            targetCost += std::abs(pickupFloor - target) * FLOOR_TRAVEL_COST;
        }
        
        return travelCost + stopCost + targetCost + (request.targetFloors.size() * STOP_COST);
    }

    if (status.committedDirection != requestDirection) {
        int totalCost = 0;
        int furthestStop = status.currentFloor;
        
        auto currentDirectionStops = (status.committedDirection == Direction::UP) ? elevator->getUpStops() : elevator->getDownStops();

        if (!currentDirectionStops.empty()) {
            if (status.committedDirection == Direction::UP) {
                furthestStop = *currentDirectionStops.rbegin();
            } else {
                furthestStop = *currentDirectionStops.begin();
            }
        }

        totalCost += std::abs(status.currentFloor - furthestStop) * FLOOR_TRAVEL_COST;
        totalCost += currentDirectionStops.size() * STOP_COST;

        totalCost += std::abs(furthestStop - pickupFloor) * FLOOR_TRAVEL_COST;
        
        auto oppositeDirectionStops = (status.committedDirection == Direction::UP) ? elevator->getDownStops() : elevator->getUpStops();
        for (int stop : oppositeDirectionStops) {
            if ((status.committedDirection == Direction::UP && stop < furthestStop && stop > pickupFloor) ||
                (status.committedDirection == Direction::DOWN && stop > furthestStop && stop < pickupFloor)) {
                totalCost += STOP_COST;
            }
        }
        
        int targetCost = 0;
        for (int target : request.targetFloors) {
            targetCost += std::abs(pickupFloor - target) * FLOOR_TRAVEL_COST;
        }
        
        return totalCost + targetCost + (request.targetFloors.size() * STOP_COST);
    }

    return INT_MAX;
}
