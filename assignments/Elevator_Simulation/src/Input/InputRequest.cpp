#include "../../inc/Input/InputRequest.h"

InputRequest::InputRequest(int requestedFloor, const std::vector<int>& targets, Direction dir) 
    : type(RequestType::ELEVATOR_REQUEST), requestedAtFloor(requestedFloor), targetFloors(targets), direction(dir) {}

InputRequest::InputRequest(int requestedFloor, int targetFloor, Direction dir) 
    : type(RequestType::ELEVATOR_REQUEST), requestedAtFloor(requestedFloor), targetFloors({targetFloor}), direction(dir) {}

InputRequest::InputRequest(RequestType type) 
    : type(type), requestedAtFloor(0), targetFloors({}), direction(Direction::IDLE) {}

InputRequest::InputRequest() 
    : type(RequestType::ELEVATOR_REQUEST), requestedAtFloor(0), targetFloors({}), direction(Direction::IDLE) {}

bool InputRequest::isValid() const {
    if (type == RequestType::SHUTDOWN_REQUEST) return true;
    if (targetFloors.empty()) return false;
    for (int target : targetFloors) {
        if (requestedAtFloor == target) return false;
    }
    return true;
}

bool InputRequest::isShutdown() const {
    return type == RequestType::SHUTDOWN_REQUEST;
}

