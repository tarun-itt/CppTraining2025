#ifndef INPUT_VALIDATION_H
#define INPUT_VALIDATION_H
#include <string>
#include <vector>
#include <optional>

#include "../Input/InputRequest.h"
#include "../Core/ElevatorSystemConfig.h"
#include "Direction.h"


class InputValidation {
public:
    struct ValidationResult {
        bool isValid;
        std::string errorMessage;
        InputRequest request;
    };

    static ValidationResult validate(const std::string& input, const ElevatorSystemConfig& config);
    
private:

    static bool isValidFormat(const std::string& input);
    static std::optional<int> parseFloor(const std::string& floorStr);
    static bool isFloorInRange(int floor, const ElevatorSystemConfig& config);
    static std::vector<std::string> split(const std::string& input, char delimiter);
};

#endif