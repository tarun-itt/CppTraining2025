#ifndef ELEVATOR_SNAPSHOT_H
#define ELEVATOR_SNAPSHOT_H

#include "Direction.h"

enum class ElevatorState {
    IDLE,
    MOVING,
    HALTED
};

struct ElevatorSnapshot {
    int id;
    int currentFloor;
    ElevatorState state;
    Direction committedDirection;
    size_t upStopsCount;
    size_t downStopsCount;
};

#endif