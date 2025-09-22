#include <sstream>
#include <algorithm>
#include <cctype>

#include "InputValidation.h"
#include "ElevatorSystemConfig.h"

namespace InputValidation {

    bool isValidFormat(const std::string& input) {
        return input.find(' ') != std::string::npos || input == "exit" || input == "quit";
    }
    
    int parseFloor(const std::string& floorStr) {
        if (floorStr.empty()) {
            return INVALID_FLOOR;
        }
        
        char firstChar = std::tolower(floorStr[0]);
        
        if (firstChar == 'g') {
            return 0;
        } else if (firstChar == 'f') {
            if (floorStr.length() < 2) {
                return INVALID_FLOOR;
            }
            std::string numStr = floorStr.substr(1);
            try {
                int floor = std::stoi(numStr);
                return (floor > 0) ? floor : INVALID_FLOOR;
            } catch (...) {
                return INVALID_FLOOR;
            }
        } else if (firstChar == 'b') {
            if (floorStr.length() < 2) {
                return INVALID_FLOOR;
            }
            std::string numStr = floorStr.substr(1);
            try {
                int floor = std::stoi(numStr);
                return (floor > 0) ? -floor : INVALID_FLOOR;
            } catch (...) {
                return INVALID_FLOOR;
            }
        }
        
        return INVALID_FLOOR;
    }
    
    std::vector<std::string> split(const std::string& input, char delimiter) {
        std::vector<std::string> parts;
        std::stringstream ss(input);
        std::string part;
        
        while (std::getline(ss, part, delimiter)) {
            parts.push_back(part);
        }
        
        return parts;
    }
    
    ValidationResult validate(const std::string& input, const ElevatorSystemConfig& config) {
        if (input == "exit" || input == "quit") {
            InputRequest request(RequestType::SHUTDOWN_REQUEST);
            return {true, "", request};
        }
        
        if (!isValidFormat(input)) {
            return {false, "Invalid format. Expected: from target1 [target2...] (e.g., f1 f6, f2 f5 g b1) or exit/quit", {}};
        }
        
        auto parts = split(input, ' ');
        if (parts.size() < 2) {
            return {false, "Invalid format. Expected: from target1 [target2...] (e.g., f1 f6, f2 f5 g b1) or exit/quit", {}};
        }
        
        std::string from = parts[0];
        int fromFloor = parseFloor(from);
        
        if (fromFloor == INVALID_FLOOR) {
            return {false, "Invalid from floor: " + from, {}};
        }
        
        if (!isFloorInRange(fromFloor, config)) {
            return {false, "Floor " + from + " is out of range. Valid range: g, f1-f" + 
                    std::to_string(config.numberOfFloors) + ", b1-b" + std::to_string(config.numberOfBasements), {}};
        }
        
        std::vector<int> targetFloors;
        for (size_t i = 1; i < parts.size(); ++i) {
            int targetFloor = parseFloor(parts[i]);
            if (targetFloor == INVALID_FLOOR) {
                return {false, "Invalid target floor: " + parts[i], {}};
            }
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
            bool hasUp = false, hasDown = false;
            for (int target : targetFloors) {
                if (target > fromFloor) hasUp = true;
                else hasDown = true;
            }
            if (hasUp && hasDown) {
                direction = Direction::IDLE;
            } else if (hasUp) {
                direction = Direction::UP;
            } else {
                direction = Direction::DOWN;
            }
        }
        
        InputRequest request(fromFloor, targetFloors, direction);
        
        return {true, "", request};
    }
    
    bool isFloorInRange(int floor, const ElevatorSystemConfig& config) {
        if (floor == 0) return true;  
        if (floor > 0) return floor <= config.numberOfFloors;
        if (floor < 0) return floor >= -config.numberOfBasements;
        return false;
    }
}