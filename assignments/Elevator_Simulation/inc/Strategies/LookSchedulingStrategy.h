#ifndef LOOK_SCHEDULING_STRATEGY_H
#define LOOK_SCHEDULING_STRATEGY_H

#include "Interfaces/IElevatorSchedulingStrategy.h"

class LookSchedulingStrategy : public IElevatorSchedulingStrategy {
public:
  int findNextStop(int currentFloor, Direction committedDirection, const std::set<int> &upStops, const std::set<int> &downStops) const override;
};

#endif