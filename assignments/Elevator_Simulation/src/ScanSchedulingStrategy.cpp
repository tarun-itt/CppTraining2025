#include <algorithm>

#include "ScanSchedulingStrategy.h"

int ScanSchedulingStrategy::findNextStop(int currentFloor, Direction committedDirection, const std::set<int>& upStops, const std::set<int>& downStops) const {

    if (committedDirection == Direction::UP) {
        auto it = upStops.lower_bound(currentFloor);
        if (it != upStops.end()) {
            return *it;
        }

        if (!downStops.empty()) {
            return *downStops.rbegin();
        }
    }
    
    else if (committedDirection == Direction::DOWN) {
        auto it = std::find_if(downStops.rbegin(), downStops.rend(),
                               [currentFloor](int floor) { return floor <= currentFloor; });
        if (it != downStops.rend()) {
            return *it;
        }

        if (!upStops.empty()) {
            return *upStops.begin();
        }
    }
    
    if (!upStops.empty()) {
        return *upStops.begin();
    }
    if (!downStops.empty()) {
        return *downStops.rbegin();
    }

    return currentFloor;
}