#include <sstream>
#include <algorithm>
#include <cctype>
#include <optional>

#include "../../inc/Utils/InputValidation.h"
#include "../../inc/Core/ElevatorSystemConfig.h"
#include "../../inc/Utils/Direction.h"

bool InputValidation::isValidFormat(const std::string& input) {
    return input.find(' ') != std::string::npos || input == "exit" || input == "quit";
}

std::optional<int> InputValidation::parseFloor(const std::string& floorStr) {
    if (floorStr.empty()) {
        return std::nullopt;
    }
    
    char firstChar = std::tolower(floorStr[0]);
    
    if (firstChar == 'g') {
        return 0;
    } else if (firstChar == 'f') {
        if (floorStr.length() < 2) {
            return std::nullopt;
        }
        std::string numStr = floorStr.substr(1);
        try {
            int floor = std::stoi(numStr);
            return (floor > 0) ? std::optional<int>(floor) : std::nullopt;
        } catch (...) {
            return std::nullopt;
        }
    } else if (firstChar == 'b') {
        if (floorStr.length() < 2) {
            return std::nullopt;
        }
        std::string numStr = floorStr.substr(1);
        try {
            int floor = std::stoi(numStr);
            return (floor > 0) ? std::optional<int>(-floor) : std::nullopt;
        } catch (...) {
            return std::nullopt;
        }
    }
    
    return std::nullopt;
}
std::vector<std::string> InputValidation::split(const std::string& input, char delimiter) {
    std::vector<std::string> parts;
    std::stringstream ss(input);
    std::string part;
    
    while (std::getline(ss, part, delimiter)) {
        parts.push_back(part);
    }
    
    return parts;
}

InputValidation::ValidationResult InputValidation::validate(const std::string& input, const ElevatorSystemConfig& config) {
    if (input == "exit" || input == "quit") {
        InputRequest request(RequestType::SHUTDOWN_REQUEST);
        return {true, "", request};
    }
    
    if (!isValidFormat(input)) {
        return {false, "Invalid format. Expected: from target1 [target2...] (e.g., f1 f6, f2 f5 g b1) or exit/quit", {}};
    }
    
    std::vector<std::string> parts = split(input, ' ');
    if (parts.size() < 2) {
        return {false, "Invalid format. Expected: from target1 [target2...] (e.g., f1 f6, f2 f5 g b1) or exit/quit", {}};
    }
    
    std::string from = parts[0];
    auto fromFloorOpt = parseFloor(from);
    
    if (!fromFloorOpt.has_value()) {
        return {false, "Invalid from floor: " + from, {}};
    }
    
    int fromFloor = fromFloorOpt.value();
    if (!isFloorInRange(fromFloor, config)) {
        return {false, "Floor " + from + " is out of range. Valid range: g, f1-f" + 
                std::to_string(config.numberOfFloors) + ", b1-b" + std::to_string(config.numberOfBasements), {}};
    }
    
    std::vector<int> targetFloors;
    for (size_t i = 1; i < parts.size(); ++i) {
        auto targetFloorOpt = parseFloor(parts[i]);
        if (!targetFloorOpt.has_value()) {
            return {false, "Invalid target floor: " + parts[i], {}};
        }
        int targetFloor = targetFloorOpt.value();
        if (!isFloorInRange(targetFloor, config)) {
            return {false, "Floor " + parts[i] + " is out of range. Valid range: g, f1-f" + 
                    std::to_string(config.numberOfFloors) + ", b1-b" + std::to_string(config.numberOfBasements), {}};
        }
        if (targetFloor == fromFloor) {
            return {false, "Target floor cannot be the same as pickup floor: " + parts[i], {}};
        }
        targetFloors.push_back(targetFloor);
    }
    
    if (targetFloors.empty()) {
        return {false, "At least one target floor is required", {}};
    }
    
    Direction direction = Direction::IDLE;
    if (targetFloors.size() == 1) {
        direction = (targetFloors[0] > fromFloor) ? Direction::UP : Direction::DOWN;
    } else {
        std::vector<int> upTargets, downTargets;
        
        for (int target : targetFloors) {
            if (target > fromFloor) {
                upTargets.push_back(target);
            } else if (target < fromFloor) {
                downTargets.push_back(target);
            }
        }
        
        if (upTargets.empty() && downTargets.empty()) {
            direction = Direction::IDLE;
        } else if (upTargets.empty()) {
            direction = Direction::DOWN;
        } else if (downTargets.empty()) {
            direction = Direction::UP;
        } else {
            if (upTargets.size() > downTargets.size()) {
                direction = Direction::UP;
            } else if (downTargets.size() > upTargets.size()) {
                direction = Direction::DOWN;
            } else {
                int closestUp = *std::min_element(upTargets.begin(), upTargets.end());
                int closestDown = *std::max_element(downTargets.begin(), downTargets.end());
                
                int distUp = closestUp - fromFloor;
                int distDown = fromFloor - closestDown;
                
                direction = (distUp <= distDown) ? Direction::UP : Direction::DOWN;
            }
        }
    }
    
    InputRequest request(fromFloor, targetFloors, direction);
    
    return {true, "", request};
}

bool InputValidation::isFloorInRange(int floor, const ElevatorSystemConfig& config) {
    if (floor == 0) return true;  
    if (floor > 0) return floor <= config.numberOfFloors;
    if (floor < 0) return floor >= -config.numberOfBasements;
    return false;
}