#include <algorithm>

#include "Strategies/LookSchedulingStrategy.h"

int LookSchedulingStrategy::findNextStop(int currentFloor, Direction committedDirection, const std::set<int> &upStops, const std::set<int> &downStops) const {

	if (committedDirection == Direction::UP) {
		auto it = upStops.upper_bound(currentFloor);
		if (it != upStops.end()) {
			return *it;
		}

		if (!downStops.empty()) {
			return *downStops.rbegin();
		}
	} 
	else if (committedDirection == Direction::DOWN) {
		auto it = downStops.lower_bound(currentFloor);
		if (it != downStops.end() && *it == currentFloor) {
			return *it;
		} else if (it != downStops.begin()) {
			--it;
			return *it;
		}

		if (!upStops.empty()) {
			return *upStops.begin();
		}
	}
	else if (committedDirection == Direction::IDLE) {
		int closestUp = -1;
		int closestDown = -1;

		if (!upStops.empty()) {
			auto it = upStops.lower_bound(currentFloor);
			if (it != upStops.end()) {
				closestUp = *it;
			}
		}

		if (!downStops.empty()) {
			auto it = downStops.lower_bound(currentFloor);
			if (it != downStops.begin()) {
				--it;
				closestDown = *it;
			}
		}

		if (closestUp != -1 && closestDown != -1) {
			int distUp = closestUp - currentFloor;
			int distDown = currentFloor - closestDown;
			return (distUp <= distDown) ? closestUp : closestDown;
		} else if (closestUp != -1) {
			return closestUp;
		} else if (closestDown != -1) {
			return closestDown;
		}
	}

	return currentFloor;
}
