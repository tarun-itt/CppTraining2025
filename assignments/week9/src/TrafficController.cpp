#include <condition_variable>
#include <iostream>
#include <fstream>

#include "TrafficController.h"

#ifdef DEV
    std::ofstream logger("debug.log", std::ios::out | std::ios::trunc);
    #define LOG(msg) logger<<msg<<std::endl;
#else
    #define LOG(msg) std::cout << msg << std::endl; 
#endif

TrafficController::TrafficController(std::vector<ILane*>& lanes, ITimer& timer, int greenLightDuration)
    : lanes(lanes), timer(timer), greenLightDuration(greenLightDuration),
      currentTime(0), simulationRunning(false), currentActiveLane(-1) {
}

TrafficController::~TrafficController() {
    simulationRunning = false;
    laneCondition.notify_all();
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
        if(controllerMutex.try_lock()){
            for (size_t currentLane = 0; currentLane < lanes.size(); ++currentLane) {
                int remainingCars = lanes[currentLane]->getRemainingCarCount();
                if (remainingCars > maxRemainingCars) {
                    maxRemainingCars = remainingCars;
                    nextLane = currentLane;
                }
            }
            currentActiveLane = nextLane;
            greenTimeLeft = greenLightDuration;
        }else {
            continue;
        }
        controllerMutex.unlock();
        laneCondition.notify_all();
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
        
        while (currentActiveLane == laneIndex && greenTimeLeft > 0) {
            if (!lanes[laneIndex]->hasCars()) {
                break;
            }
            
            if (lanes[laneIndex]->processCar()) {
                int currentCarNumber = lanes[laneIndex]->getInitialCarCount() - lanes[laneIndex]->getRemainingCarCount();
                std::string carName = static_cast<char>('A' + laneIndex) + std::to_string(currentCarNumber);
                
                currentTime++;
                int remainingTime = greenTimeLeft;
                
                printStatus(currentTime, laneIndex, remainingTime, carName);
                --greenTimeLeft;
                
                if (greenTimeLeft <= 0) {
                    timer.sleep(CAR_PASS_DURATION);
                    break;
                }
            }
            
            timer.sleep(CAR_PASS_DURATION);
        }
    }
}

void TrafficController::printStatus(int time, int laneIndex, int remainingTime, const std::string& carName) {
    std::string status = "Time " + std::to_string(time) + ": lane " + static_cast<char>('A' + laneIndex) + " (green time remaining " + std::to_string(remainingTime) + "s), car " + carName + " passed";
    
    LOG(status);
}

bool TrafficController::hasCarsInAnyLane() {
    for (auto& lane : lanes) {
        if (lane->hasCars()) {
            return true;
        }
    }
    return false;
}