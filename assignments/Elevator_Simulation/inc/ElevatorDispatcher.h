#ifndef ELEVATOR_DISPATCHER_H
#define ELEVATOR_DISPATCHER_H

#include <vector>
#include <thread>
#include <atomic>
#include <functional> 

#include "IBlockingQueue.h"
#include "InputRequest.h"
#include "Elevator.h"
#include "IElevatorAssignmentStrategy.h"
#include "MessageSender.h"

class ElevatorDispatcher {
public:

    ElevatorDispatcher(IBlockingQueue<InputRequest>* queue,
                         IElevatorAssignmentStrategy* strategy,
                         std::vector<Elevator*>& elevators,
                         std::function<void()> shutdownCallback,
                         MessageSender* messageSender = nullptr);

    ~ElevatorDispatcher();

    ElevatorDispatcher(const ElevatorDispatcher&) = delete;
    ElevatorDispatcher& operator=(const ElevatorDispatcher&) = delete;

    void start();

    void stop();

private:

    void dispatchLoop();

    std::atomic<bool> running;
    std::thread dispatcherThread;

    IBlockingQueue<InputRequest>* requests;         
    IElevatorAssignmentStrategy* strategy;    
    std::vector<Elevator*>& elevators;               
    std::function<void()> shutdownCallback;
    MessageSender* messageSender;             
};

#endif