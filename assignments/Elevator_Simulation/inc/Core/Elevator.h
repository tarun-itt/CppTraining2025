#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <set>
#include <unordered_map>
#include <vector>
#include <mutex>
#include <thread>
#include <atomic>
#include <string>

#include "Interfaces/ISubject.h"
#include "Interfaces/IElevatorSchedulingStrategy.h"
#include "Utils/Direction.h"
#include "Core/ElevatorSnapshot.h"

class Elevator : public ISubject {
public:
    Elevator(int id, IElevatorSchedulingStrategy* scheduler);
    ~Elevator();

    Elevator(const Elevator&) = delete;
    Elevator& operator=(const Elevator&) = delete;

    void start();
    void stop();
    void addRequest(int pickupFloor, const std::vector<int>& targetFloors);
    void addRequest(int pickupFloor, int targetFloor);
    ElevatorSnapshot getSnapshot() const;
    std::set<int> getUpStops() const;
    std::set<int> getDownStops() const;

    void addObserver(IObserver* observer) override;
    void removeObserver(IObserver* observer) override;
    void notifyObservers() override;

private:
    void run();

    const int id;
    IElevatorSchedulingStrategy* scheduler;

    std::atomic<bool> operating;
    std::atomic<int> currentFloor;
    std::atomic<ElevatorState> state;
    std::atomic<Direction> committedDirection;

    std::set<int> upStops;
    std::set<int> downStops;
    std::unordered_map<int, std::vector<int>> pendingDropoffs;
    mutable std::mutex elevatorMutex;

    std::vector<IObserver*> observers;
    std::mutex observerMutex;
    std::thread elevatorThread;
};

#endif