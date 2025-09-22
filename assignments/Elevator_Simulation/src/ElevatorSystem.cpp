#include <iostream>
#include <stdexcept>
#include <vector>

#include "ElevatorSystem.h"
#include "RequestsQueue.h"
#include "FileInputReader.h"
#include "ConsoleOutput.h"
#include "DisplayManager.h"
#include "ElevatorDispatcher.h"
#include "Elevator.h"
#include "CostBasedStrategy.h"
#include "ScanSchedulingStrategy.h"
#include "ElevatorSystemPrintable.h"
#include "MessageSender.h"

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
    std::vector<ElevatorSnapshot> snapshots;
    snapshots.reserve(elevators.size());
    for (const auto* elevator : elevators) {
        snapshots.push_back(elevator->getSnapshot());}

    auto systemPrintable = new ElevatorSystemPrintable(snapshots);
    
    if (displayQueue) {
        RenderRequest request(RenderOperation::Display, systemPrintable, "system_status_table");
        displayQueue->push(request);
    }
}

void ElevatorSystem::createComponents() {
    requestQueue = new RequestsQueue<InputRequest>();
    displayQueue = new RequestsQueue<RenderRequest>();
    messageSender = new MessageSender(displayQueue);
    inputProvider = new FileInputReader("requests.txt", requestQueue, config, messageSender);
    outputProcessor = new ConsoleOutput(displayQueue);
    assignmentStrategy = new CostBasedStrategy(messageSender);
    schedulingStrategy = new ScanSchedulingStrategy();

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

    onStateChanged();
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
