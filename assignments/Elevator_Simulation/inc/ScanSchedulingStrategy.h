#ifndef SCAN_SCHEDULING_STRATEGY_H
#define SCAN_SCHEDULING_STRATEGY_H

#include "IElevatorSchedulingStrategy.h"

class ScanSchedulingStrategy : public IElevatorSchedulingStrategy {
public:
  int findNextStop(int currentFloor, Direction committedDirection, const std::set<int> &upStops, const std::set<int> &downStops) const override;
};

#endif