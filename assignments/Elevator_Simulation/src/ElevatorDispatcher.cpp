#include <iostream>

#include "ElevatorDispatcher.h"

ElevatorDispatcher::ElevatorDispatcher(IBlockingQueue<InputRequest>* queue, IElevatorAssignmentStrategy* strategy, std::vector<Elevator*>& elevators, std::function<void()> shutdownCallback,MessageSender* messageSender)
    : running(false),
      requests(queue),
      strategy(strategy),
      elevators(elevators),
      shutdownCallback(shutdownCallback),
      messageSender(messageSender) {}

ElevatorDispatcher::~ElevatorDispatcher() {
    stop();
}

void ElevatorDispatcher::start() {
    if (running) {
        return;
    }
    running = true;
    dispatcherThread = std::thread(&ElevatorDispatcher::dispatchLoop, this);
}

void ElevatorDispatcher::stop() {
    if (!running) {
        return;
    }
    running = false;
    if (dispatcherThread.joinable()) {
        dispatcherThread.join();
    }
}

void ElevatorDispatcher::dispatchLoop() {
    while (running) {
        InputRequest request = requests->try_pop();

        if (!request.isValid()) {
            continue;
        }

        if (request.isShutdown()) {
            if (messageSender) {
                messageSender->sendNormal("Exiting program.");
            }
            if (shutdownCallback) {
                shutdownCallback();
            }
            break;
        }

        if (strategy) {
            Elevator* selectedElevator = strategy->selectElevator(request, elevators);
            if (selectedElevator) {
                selectedElevator->addRequest(request.requestedAtFloor, request.targetFloors);
            }
        }
    }
}
