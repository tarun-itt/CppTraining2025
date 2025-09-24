#include <iostream>
#include <stdexcept>
#include <vector>

#include "Core/ElevatorSystem.h"

ElevatorSystem::ElevatorSystem(const ElevatorSystemConfig& config)
    : config(config), running(false)
{
    requestQueue = nullptr;
    displayQueue = nullptr;
    inputProvider = nullptr;
    outputProcessor = nullptr;
    assignmentStrategy = nullptr;
    schedulingStrategy = nullptr;
    dispatcher = nullptr;
    messageSender = nullptr;

    try {
        createComponents();
        wireDependencies();
    } catch (const std::exception& e) {
        if (messageSender) {
            messageSender->sendError("Error during ElevatorSystem setup: " + std::string(e.what()));
        }
        cleanupComponents();
        throw;
    }
}

ElevatorSystem::~ElevatorSystem() {
    shutdown();
    cleanupComponents();
}

void ElevatorSystem::onStateChanged() {
    std::lock_guard<std::mutex> lock(displayUpdateMutex);
    std::vector<ElevatorSnapshot> elevatorSnapshots;
    elevatorSnapshots.reserve(elevators.size());

    for (const auto* elevator : elevators) {
        elevatorSnapshots.push_back(elevator->getSnapshot());
    }

    IPrintable *elevatorSystemTable = new ElevatorSystemPrintable(elevatorSnapshots);
    
    if (displayQueue) {
        RenderRequest request(RenderOperation::Display, elevatorSystemTable, "system_status_table");
        displayQueue->push(request);
    }
}

void ElevatorSystem::createComponents() {
    requestQueue = new RequestsQueue<InputRequest>();
    displayQueue = new RequestsQueue<RenderRequest>();
    messageSender = new MessageSender(displayQueue);
    inputProvider = new FileInputReader(config.inputFilePath, requestQueue, config, messageSender);
    outputProcessor = new ConsoleOutput(displayQueue);
    assignmentStrategy = new CostBasedStrategy(messageSender);
    schedulingStrategy = new LookSchedulingStrategy();

    elevators.reserve(config.numberOfElevators);
    for (int i = 0; i < config.numberOfElevators; ++i) {
        elevators.push_back(new Elevator(i, schedulingStrategy));
    }


    auto shutdownCallback = [this]() { this->shutdown(); };
    dispatcher = new ElevatorDispatcher(requestQueue, assignmentStrategy, elevators, shutdownCallback, messageSender);
}

void ElevatorSystem::wireDependencies() {
    DisplayManager::initialize(displayQueue);

    for (auto* elevator : elevators) {
        elevator->addObserver(this);
    }

}

void ElevatorSystem::cleanupComponents() {
    delete dispatcher;

    for (auto elevator : elevators) delete elevator;
    delete schedulingStrategy;
    delete assignmentStrategy;
    delete outputProcessor;
    delete inputProvider;
    delete messageSender;
    delete displayQueue;
    delete requestQueue;
    elevators.clear();
}

void ElevatorSystem::start() {
    if (running) {
        messageSender->sendWarning("Elevator system is already running.");
        return;
    }
    running = true;
    startAllThreads();
}

void ElevatorSystem::shutdown() {
    bool expected = true;
    if (running.compare_exchange_strong(expected, false)) {
        stopAllThreads();
        shutdownCondition.notify_all();
    }
}

bool ElevatorSystem::isRunning() const {
    return running.load();
}

void ElevatorSystem::startAllThreads() {
    if (outputProcessor) outputProcessor->start();
    if (inputProvider) inputProvider->start();
    if (dispatcher) dispatcher->start();
    for (Elevator* elevator : elevators) {
        elevator->start();
    }
}

void ElevatorSystem::stopAllThreads() {
    if (inputProvider) inputProvider->stop();
    if (requestQueue) requestQueue->shutdown();

    for (Elevator* elevator : elevators) {
        elevator->stop();
    }
    
    if (displayQueue) displayQueue->shutdown();
    if (outputProcessor) outputProcessor->stop();
}

void ElevatorSystem::waitForShutdown() {
    std::unique_lock<std::mutex> lock(shutdownMutex);
    shutdownCondition.wait(lock, [this] { return !running.load(); });
}