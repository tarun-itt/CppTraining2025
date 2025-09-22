#ifndef INPUT_VALIDATION_H
#define INPUT_VALIDATION_H
#include <string>
#include <vector>

#include "InputRequest.h"
#include "ElevatorSystemConfig.h"


namespace InputValidation {
    struct ValidationResult {
        bool isValid;
        std::string errorMessage;
        InputRequest request;
    };
    
    ValidationResult validate(const std::string& input);
    ValidationResult validate(const std::string& input, const ElevatorSystemConfig& config);
    bool isValidFormat(const std::string& input);
    int parseFloor(const std::string& floorStr);
    bool isFloorInRange(int floor, const ElevatorSystemConfig& config);
    std::vector<std::string> split(const std::string& input, char delimiter);
    
    const int INVALID_FLOOR = -999;
}

#endif