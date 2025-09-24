#ifndef ELEVATOR_SYSTEM_CONFIG_H
#define ELEVATOR_SYSTEM_CONFIG_H

#include <string>

struct ElevatorSystemConfig {
  int numberOfElevators;
  int numberOfFloors;
  int numberOfBasements;
  std::string inputFilePath;

  ElevatorSystemConfig(): numberOfElevators(2), numberOfFloors(8), numberOfBasements(2), inputFilePath("requests.txt") {}

  bool isValid() const {
    return numberOfElevators > 0 && numberOfFloors > 0 && numberOfBasements >= 0;
  }
};

#endif