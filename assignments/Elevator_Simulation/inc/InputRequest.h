#ifndef INPUT_REQUEST_H
#define INPUT_REQUEST_H

#include <string>
#include <vector>

#include "Direction.h"

enum class RequestType {
    ELEVATOR_REQUEST,
    SHUTDOWN_REQUEST
};

struct InputRequest {
    RequestType type;
    int requestedAtFloor;
    std::vector<int> targetFloors;
    Direction direction;
    
    InputRequest(int requestedFloor, const std::vector<int>& targets, Direction dir): type(RequestType::ELEVATOR_REQUEST), requestedAtFloor(requestedFloor), targetFloors(targets), direction(dir) {}
    
    InputRequest(int requestedFloor, int targetFloor, Direction dir): type(RequestType::ELEVATOR_REQUEST), requestedAtFloor(requestedFloor), targetFloors({targetFloor}), direction(dir) {}
    
    InputRequest(RequestType type): type(type), requestedAtFloor(0), targetFloors({}), direction(Direction::IDLE) {}
    
    InputRequest(): type(RequestType::ELEVATOR_REQUEST), requestedAtFloor(0), targetFloors({}), direction(Direction::IDLE) {}
    
    bool isValid() const {
        if (type == RequestType::SHUTDOWN_REQUEST) return true;
        if (targetFloors.empty()) return false;
        for (int target : targetFloors) {
            if (requestedAtFloor == target) return false;
        }
        return true;
    }
    
    bool isShutdown() const {
        return type == RequestType::SHUTDOWN_REQUEST;
    }
    
    std::string toString() const {
        if (type == RequestType::SHUTDOWN_REQUEST) {
            return "Shutdown Request";
        }
        std::string result = "Request: Floor " + std::to_string(requestedAtFloor) + " -> ";
        for (size_t i = 0; i < targetFloors.size(); ++i) {
            if (i > 0) result += ", ";
            result += std::to_string(targetFloors[i]);
        }
        result += " (" + directionToString(direction) + ")";
        return result;
    }
    
private:
    std::string directionToString(Direction dir) const {
        switch (dir) {
            case Direction::UP: return "UP";
            case Direction::DOWN: return "DOWN";
            case Direction::IDLE: return "IDLE";
            default: return "UNKNOWN";
        }
    }
};

#endif