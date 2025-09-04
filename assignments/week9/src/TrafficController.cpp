#include <iostream>
#include "TrafficController.h"

TrafficController::TrafficController(std::vector<ILane*>& lanes, ITimer& timer, int greenLightDuration)
    : lanes(lanes), timer(timer), greenLightDuration(greenLightDuration), 
      currentTime(0), simulationRunning(false), currentActiveLane(-1) {
    
    laneReady.resize(lanes.size(), false);
}

TrafficController::~TrafficController() {
}

void TrafficController::run() {
    std::vector<std::thread> laneWorkers;
    simulationRunning = true;
    
    for (size_t i = 0; i < lanes.size(); ++i) {
        laneWorkers.emplace_back(&TrafficController::laneWorker, this, i);
    }
    
    while (simulationRunning) {
        if (!hasCarsInAnyLane()) {
            simulationRunning = false;
            break;
        }
        
        int nextLane = -1;
        for (size_t currentLane = 0; currentLane < lanes.size(); ++currentLane) {
            int laneIndex = (currentActiveLane + 1 + currentLane) % lanes.size();
            if (lanes[laneIndex]->hasCars()) {
                nextLane = laneIndex;
                break;
            }
        }
        
        if (nextLane == -1) {
            simulationRunning = false;
            break;
        }
        
        {
            std::lock_guard<std::mutex> lock(controllerMutex);
            currentActiveLane = nextLane;
            laneReady[nextLane] = true;
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
            laneReady[nextLane] = false;
        }
    }
    
    {
        std::lock_guard<std::mutex> lock(controllerMutex);
        for (size_t i = 0; i < laneReady.size(); ++i) {
            laneReady[i] = false;
        }
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
            return !simulationRunning || laneReady[laneIndex];
        });
        
        if (!simulationRunning) break;
        
        while (simulationRunning && currentActiveLane == laneIndex && lanes[laneIndex]->hasCars()) {
            lock.unlock();
            
            if (lanes[laneIndex]->processCar()) {
                currentTime++;
                int remainingTime = greenLightDuration - (currentTime % greenLightDuration);
                int currentCarNumber = lanes[laneIndex]->getInitialCarCount() - lanes[laneIndex]->getRemainingCarCount();
                std::string carName = static_cast<char>('A' + laneIndex) + std::to_string(currentCarNumber);
                printStatus(currentTime, laneIndex, remainingTime, carName);
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