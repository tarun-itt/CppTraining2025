#include <iostream>
#include "TrafficController.h"

TrafficController::TrafficController(std::vector<ILane*>& lanes, ITimer& timer, int greenLightDuration)
    : lanes(lanes), timer(timer), greenLightDuration(greenLightDuration), 
      currentTime(0), simulationRunning(false), currentActiveLane(-1) {
}

TrafficController::~TrafficController() {
}

void TrafficController::run() {
    std::vector<std::thread> laneWorkers;
    simulationRunning = true;
    currentTime = 0;
    
    for (size_t laneIndex = 0; laneIndex < lanes.size(); ++laneIndex) {
        laneWorkers.emplace_back(&TrafficController::laneWorker, this, laneIndex);
    }
    
    while (simulationRunning) {
        if (!hasCarsInAnyLane()) {
            simulationRunning = false;
            break;
        }
        
        int nextLane = -1;
        int maxRemainingCars = 0;
        for (size_t currentLane = 0; currentLane < lanes.size(); ++currentLane) {
            int remainingCars = lanes[currentLane]->getRemainingCarCount();
            if (remainingCars > maxRemainingCars) {
                maxRemainingCars = remainingCars;
                nextLane = currentLane;
            }
        }
        
        if (nextLane == -1) {
            simulationRunning = false;
            break;
        }
        
        {
            std::lock_guard<std::mutex> lock(controllerMutex);
            currentActiveLane = nextLane;
        }
        laneCondition.notify_all();
        
        for (int iteration = 0; iteration < greenLightDuration; ++iteration) {
            if (!simulationRunning) break;
            
            if (!lanes[nextLane]->hasCars()) {
                break;
            }
            
            timer.sleep(CAR_PASS_DURATION);
        }
        
        {
            std::lock_guard<std::mutex> lock(controllerMutex);
        }
    }
    
    {
        std::lock_guard<std::mutex> lock(controllerMutex);
    }
    laneCondition.notify_all();

    for (auto& worker : laneWorkers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

void TrafficController::laneWorker(int laneIndex) {
    while (simulationRunning) {
        std::unique_lock<std::mutex> lock(controllerMutex);
        laneCondition.wait(lock, [this, laneIndex]() {
            return !simulationRunning || currentActiveLane == laneIndex;
        });
        
        while (simulationRunning) {
            if (currentActiveLane != laneIndex || !lanes[laneIndex]->hasCars()) {
                break;
            }
            
            lock.unlock();
            
            if (lanes[laneIndex]->processCar()) {
                
                int currentCarNumber = lanes[laneIndex]->getInitialCarCount() - lanes[laneIndex]->getRemainingCarCount();
                int remainingTime = greenLightDuration - ((currentCarNumber-1) % greenLightDuration);
                std::string carName = static_cast<char>('A' + laneIndex) + std::to_string(currentCarNumber);
                printStatus(currentTime+1, laneIndex, remainingTime, carName);
                currentTime++;
            }
            
            timer.sleep(CAR_PASS_DURATION);
            
            lock.lock();
        }
    }
}

void TrafficController::printStatus(int time, int laneIndex, int remainingTime, const std::string& carName) {
    std::lock_guard<std::mutex> lock(controllerMutex);
    std::cout << "Time " << time << ": lane " << static_cast<char>('A' + laneIndex) << " (green time remaining " << remainingTime << "s), car " << carName << " passed" << std::endl;
}

bool TrafficController::hasCarsInAnyLane() {
    for (auto& lane : lanes) {
        if (lane->hasCars()) {
            return true;
        }
    }
    return false;
}