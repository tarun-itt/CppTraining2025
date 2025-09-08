#ifndef TRAFFICCONTROLLER_H
#define TRAFFICCONTROLLER_H

#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "ILane.h"
#include "ITimer.h"

#define CAR_PASS_DURATION 1

class TrafficController {
public:
    TrafficController(std::vector<ILane*>& lanes, ITimer& timer, int greenLightDuration = 2);
    ~TrafficController();

    void run();

private:
    void laneWorker(int laneIndex);
    void printStatus(int time, int laneIndex, int remainingTime, const std::string& carName);
    bool hasCarsInAnyLane();

    std::vector<ILane*>& lanes;
    ITimer& timer;
    int greenLightDuration;
    int currentTime;
    bool simulationRunning;
    int currentActiveLane;
    int greenTimeLeft;
    
    std::mutex controllerMutex;
    std::condition_variable laneCondition;
};

#endif