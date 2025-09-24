#ifndef INPUT_REQUEST_H
#define INPUT_REQUEST_H

#include <string>
#include <vector>

#include "Utils/Direction.h"

enum class RequestType {
    ELEVATOR_REQUEST,
    SHUTDOWN_REQUEST
};

struct InputRequest {
    RequestType type;
    int requestedAtFloor;
    std::vector<int> targetFloors;
    Direction direction;
    
    InputRequest(int requestedFloor, const std::vector<int>& targets, Direction dir);
    InputRequest(int requestedFloor, int targetFloor, Direction dir);
    InputRequest(RequestType type);
    InputRequest();
    
    bool isValid() const;
    bool isShutdown() const;
};

#endif