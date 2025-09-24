#include <climits>
#include <iostream>
#include <algorithm>

#include "Strategies/CostBasedStrategy.h"

CostBasedStrategy::CostBasedStrategy(MessageSender* messageSender)
    : messageSender(messageSender) {}

Elevator* CostBasedStrategy::selectElevator(const InputRequest& request,
                                              const std::vector<Elevator*>& availableElevators) {
    Elevator* bestElevator = nullptr;
    int minCost = INT_MAX;


    for (auto* elevator : availableElevators) {
        int cost = calculateCost(elevator, request);

        if (cost < minCost) {
            minCost = cost;
            bestElevator = elevator;
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
        int baseCost = std::abs(status.currentFloor - pickupFloor) * FloorTravelCost;
        int targetCost = 0;
        
        for (int target : request.targetFloors) {
            targetCost += std::abs(pickupFloor - target) * FloorTravelCost;
        }
        
        return baseCost + targetCost + (request.targetFloors.size() * StopCost);
    }

    if (status.committedDirection == requestDirection || requestDirection == Direction::IDLE) {
        if ((requestDirection == Direction::UP && status.currentFloor > pickupFloor) ||
            (requestDirection == Direction::DOWN && status.currentFloor < pickupFloor)) {
            return INT_MAX;
        }

        int travelCost = std::abs(status.currentFloor - pickupFloor) * FloorTravelCost;
        int stopCost = 0;
        
        auto stops = (requestDirection == Direction::UP) ? elevator->getUpStops() : elevator->getDownStops();
        for (int stop : stops) {
            if ((requestDirection == Direction::UP && stop > status.currentFloor && stop < pickupFloor) ||
                (requestDirection == Direction::DOWN && stop < status.currentFloor && stop > pickupFloor)) {
                stopCost += StopCost;
            }
        }
        
        int targetCost = 0;
        for (int target : request.targetFloors) {
            targetCost += std::abs(pickupFloor - target) * FloorTravelCost;
        }
        
        return travelCost + stopCost + targetCost + (request.targetFloors.size() * StopCost);
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

        totalCost += std::abs(status.currentFloor - furthestStop) * FloorTravelCost;
        totalCost += currentDirectionStops.size() * StopCost;

        totalCost += std::abs(furthestStop - pickupFloor) * FloorTravelCost;
        
        auto oppositeDirectionStops = (status.committedDirection == Direction::UP) ? elevator->getDownStops() : elevator->getUpStops();
        for (int stop : oppositeDirectionStops) {
            if ((status.committedDirection == Direction::UP && stop < furthestStop && stop > pickupFloor) ||
                (status.committedDirection == Direction::DOWN && stop > furthestStop && stop < pickupFloor)) {
                totalCost += StopCost;
            }
        }
        
        int targetCost = 0;
        for (int target : request.targetFloors) {
            targetCost += std::abs(pickupFloor - target) * FloorTravelCost;
        }
        
        return totalCost + targetCost + (request.targetFloors.size() * StopCost);
    }

    return INT_MAX;
}
