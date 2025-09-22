#include <chrono>
#include <algorithm>
#include <iostream>

#include "Elevator.h"
#include "IObserver.h"

const std::chrono::seconds FLOOR_TRAVEL_DURATION{1};
const std::chrono::seconds HALT_DURATION{3};

Elevator::Elevator(int id, IElevatorSchedulingStrategy* scheduler)
    : id(id),
      scheduler(scheduler),
      operating(false),
      currentFloor(0),
      state(ElevatorState::IDLE),
      direction(Direction::IDLE),
      committedDirection(Direction::IDLE) {}

Elevator::~Elevator() {
    stop();
}

void Elevator::start() {
    if (operating) return;
    operating = true;
    elevatorThread = std::thread(&Elevator::run, this);
}

void Elevator::stop() {
    if (!operating) return;
    operating = false;
    if (elevatorThread.joinable()) {
        elevatorThread.join();
    }
}

void Elevator::addRequest(int pickupFloor, const std::vector<int>& targetFloors) {
    std::lock_guard<std::mutex> lock(stopsMutex);
    int currentFloorSnapshot = currentFloor.load();
    
    if (pickupFloor == currentFloorSnapshot) {
        for (int targetFloor : targetFloors) {
            if (targetFloor > currentFloorSnapshot) upStops.insert(targetFloor);
            else downStops.insert(targetFloor);
        }
    } else {
        if (pickupFloor > currentFloorSnapshot) upStops.insert(pickupFloor);
        else downStops.insert(pickupFloor);
        
        pendingDropoffs[pickupFloor].insert(pendingDropoffs[pickupFloor].end(), 
                                           targetFloors.begin(), targetFloors.end());
    }
}

void Elevator::addRequest(int pickupFloor, int targetFloor) {
    addRequest(pickupFloor, std::vector<int>{targetFloor});
}

ElevatorSnapshot Elevator::getSnapshot() const {
    std::lock_guard<std::mutex> lock(stopsMutex);
    return {
        id,
        currentFloor,
        state,
        committedDirection,
        upStops.size(),
        downStops.size()
    };
}

std::set<int> Elevator::getUpStops() const {
    std::lock_guard<std::mutex> lock(stopsMutex);
    return upStops;
}

std::set<int> Elevator::getDownStops() const {
    std::lock_guard<std::mutex> lock(stopsMutex);
    return downStops;
}

void Elevator::addObserver(IObserver* observer) {
    std::lock_guard<std::mutex> lock(observerMutex);
    observers.push_back(observer);
}

void Elevator::removeObserver(IObserver* observer) {
    std::lock_guard<std::mutex> lock(observerMutex);
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Elevator::notifyObservers() {
    std::lock_guard<std::mutex> lock(observerMutex);
    for (IObserver* observer : observers) {
        if (observer) {
            observer->onStateChanged();
        }
    }
}

void Elevator::run() {
    notifyObservers();

    while (operating) {
        std::unique_lock<std::mutex> lock(stopsMutex);
        if (upStops.empty() && downStops.empty()) {
            state = ElevatorState::IDLE;
            committedDirection = Direction::IDLE;
            lock.unlock();
            notifyObservers();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }

        int targetFloor = scheduler->findNextStop(currentFloor, committedDirection, upStops, downStops);

        if (targetFloor > currentFloor) {
            committedDirection = Direction::UP;
        } else if (targetFloor < currentFloor) {
            committedDirection = Direction::DOWN;
        }
        
        lock.unlock();

        if (targetFloor != currentFloor) {
            state = ElevatorState::MOVING;
            direction = (targetFloor > currentFloor) ? Direction::UP : Direction::DOWN;
            
            while (currentFloor != targetFloor) {
                if (!operating) return;
                std::this_thread::sleep_for(FLOOR_TRAVEL_DURATION);
                currentFloor = currentFloor + (direction == Direction::UP ? 1 : -1);
                notifyObservers();
            }
        }
        
        state = ElevatorState::HALTED;
        direction = Direction::IDLE;
        notifyObservers();
        std::this_thread::sleep_for(HALT_DURATION);
       
        lock.lock();
        if (upStops.count(currentFloor)) upStops.erase(currentFloor);
        if (downStops.count(currentFloor)) downStops.erase(currentFloor);

        if (pendingDropoffs.count(currentFloor)) {
            for (int dest : pendingDropoffs.at(currentFloor)) {
                if (dest > currentFloor) upStops.insert(dest);
                else downStops.insert(dest);
            }
            pendingDropoffs.erase(currentFloor);
        }
    }
}