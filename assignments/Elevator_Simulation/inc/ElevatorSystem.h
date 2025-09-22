#ifndef ELEVATOR_SYSTEM_H
#define ELEVATOR_SYSTEM_H

#include <vector>
#include <atomic>
#include <chrono>
#include <mutex>

#include "ElevatorSystemConfig.h"
#include "IObserver.h"
#include "MessageSender.h"

template<typename T> class IBlockingQueue;
struct InputRequest;
struct RenderRequest;
class IInputReader;
class IOutputProcessor;
class IElevatorAssignmentStrategy;
class IElevatorSchedulingStrategy;
class Elevator;
class ElevatorDispatcher;

class ElevatorSystem : public IObserver {
public:
    explicit ElevatorSystem(const ElevatorSystemConfig& config);
    ~ElevatorSystem();

    ElevatorSystem(const ElevatorSystem&) = delete;
    ElevatorSystem& operator=(const ElevatorSystem&) = delete;

    void start();
    void shutdown();
    bool isRunning() const;

    void onStateChanged() override;

private:
    void createComponents();
    void wireDependencies();
    void cleanupComponents();
    void startAllThreads();
    void stopAllThreads();

    mutable std::mutex displayUpdateMutex;
    std::chrono::steady_clock::time_point lastDisplayUpdateTime;

    ElevatorSystemConfig config;
    std::atomic<bool> running;
    IBlockingQueue<InputRequest>* requestQueue;
    IBlockingQueue<RenderRequest>* displayQueue;
    IInputReader* inputProvider;
    IOutputProcessor* outputProcessor;
    IElevatorAssignmentStrategy* assignmentStrategy;
    IElevatorSchedulingStrategy* schedulingStrategy;
    std::vector<Elevator*> elevators;
    ElevatorDispatcher* dispatcher;
    MessageSender* messageSender;
};

#endif