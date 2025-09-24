#ifndef I_ELEVATOR_SCHEDULING_STRATEGY_H
#define I_ELEVATOR_SCHEDULING_STRATEGY_H

#include <set>

#include "Utils/Direction.h"

class IElevatorSchedulingStrategy {
public:
  virtual ~IElevatorSchedulingStrategy() = default;

  virtual int findNextStop(int currentFloor, Direction committedDirection, const std::set<int> &upStops, const std::set<int> &downStops) const = 0;
};

#endif