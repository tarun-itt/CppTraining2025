#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <chrono>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <mutex>

#include "mocks/MockBlockingQueue.h"
#include "mocks/MockElevatorAssignmentStrategy.h"
#include "mocks/MockElevatorSchedulingStrategy.h"
#include "../inc/ElevatorDispatcher.h"
#include "../inc/IBlockingQueue.h"
#include "../inc/Elevator.h"
#include "../inc/MessageSender.h"
#include "../inc/InputRequest.h"
#include "../inc/Direction.h"

using ::testing::Return;
using ::testing::_;
using ::testing::InSequence;
using ::testing::AtLeast;
using ::testing::Exactly;
using ::testing::Invoke;
using ::testing::DoAll;

class GivenTestingElevatorDispatcherThreading : public ::testing::Test {
    protected:
        MockBlockingQueue<InputRequest>* mockQueue;
        MockElevatorAssignmentStrategy* mockAssignmentStrategy;
        MessageSender* messageSender;
        
        Elevator* elevator1;
        Elevator* elevator2;
        std::vector<Elevator*> elevators;
        ElevatorDispatcher* dispatcher;
        
        std::atomic<bool> shutdownReceived{false};
        std::condition_variable shutdownCondition;
        std::mutex shutdownMutex;

        void SetUp() override {
            mockQueue = new MockBlockingQueue<InputRequest>();
            mockAssignmentStrategy = new MockElevatorAssignmentStrategy();
            messageSender = nullptr;
            
            elevator1 = new Elevator(0, new MockElevatorSchedulingStrategy());
            elevator2 = new Elevator(1, new MockElevatorSchedulingStrategy());
            elevators.push_back(elevator1);
            elevators.push_back(elevator2);

            auto shutdownCallback = [this]() { 
                std::lock_guard<std::mutex> lock(this->shutdownMutex);
                this->shutdownReceived = true;
                this->shutdownCondition.notify_all();
            };
            
            dispatcher = new ElevatorDispatcher(mockQueue, mockAssignmentStrategy, elevators, shutdownCallback, messageSender);
        }

        void TearDown() override {
            if (dispatcher) {
                dispatcher->stop();
                delete dispatcher;
            }
            delete elevator1;
            delete elevator2;
            delete mockAssignmentStrategy;
            delete mockQueue;
        }

        bool waitForShutdown(std::chrono::seconds timeout) {
            std::unique_lock<std::mutex> lock(shutdownMutex);
            return shutdownCondition.wait_for(lock, timeout, [this] { return shutdownReceived.load(); });
        }

        void resetShutdownState() {
            std::lock_guard<std::mutex> lock(shutdownMutex);
            shutdownReceived = false;
        }
};

TEST_F(GivenTestingElevatorDispatcherThreading, WhenStartCalledThenDispatcherThreadStartsRunning) {
    
    InputRequest shutdownRequest(RequestType::SHUTDOWN_REQUEST);
    EXPECT_CALL(*mockQueue, try_pop())
        .WillOnce(Return(shutdownRequest));
    
    dispatcher->start();
    
    bool shutdownReceived = waitForShutdown(std::chrono::seconds(1));
    EXPECT_TRUE(shutdownReceived);
}

TEST_F(GivenTestingElevatorDispatcherThreading, WhenStopCalledThenDispatcherThreadStopsAndJoins) {
    dispatcher->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    dispatcher->stop();
    
    resetShutdownState();
    InputRequest shutdownRequest(RequestType::SHUTDOWN_REQUEST);
    EXPECT_CALL(*mockQueue, try_pop())
        .WillOnce(Return(shutdownRequest));
    
    dispatcher->start();
    bool shutdownReceived = waitForShutdown(std::chrono::seconds(1));
    EXPECT_TRUE(shutdownReceived);
}

TEST_F(GivenTestingElevatorDispatcherThreading, WhenStartCalledTwiceThenSecondCallIsIgnored) {
    dispatcher->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    dispatcher->start();
    
    resetShutdownState();
    InputRequest shutdownRequest(RequestType::SHUTDOWN_REQUEST);
    EXPECT_CALL(*mockQueue, try_pop())
        .WillOnce(Return(shutdownRequest));
    
    bool shutdownReceived = waitForShutdown(std::chrono::seconds(1));
    EXPECT_TRUE(shutdownReceived);
}

TEST_F(GivenTestingElevatorDispatcherThreading, WhenStopCalledTwiceThenSecondCallIsIgnored) {
    dispatcher->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    dispatcher->stop();
    
    dispatcher->stop();
    
    resetShutdownState();
    InputRequest shutdownRequest(RequestType::SHUTDOWN_REQUEST);
    EXPECT_CALL(*mockQueue, try_pop())
        .WillOnce(Return(shutdownRequest));
    
    dispatcher->start();
    bool shutdownReceived = waitForShutdown(std::chrono::seconds(1));
    EXPECT_TRUE(shutdownReceived);
}


TEST_F(GivenTestingElevatorDispatcherThreading, WhenDispatchLoopReceivesInvalidRequestThenContinuesRunning) {
    InputRequest invalidRequest;
    InputRequest validRequest(2, 6, Direction::UP);
    InputRequest shutdownRequest(RequestType::SHUTDOWN_REQUEST);
    
    EXPECT_CALL(*mockQueue, try_pop())
        .WillOnce(Return(invalidRequest))
        .WillOnce(Return(validRequest))
        .WillOnce(Return(shutdownRequest));
    
    EXPECT_CALL(*mockAssignmentStrategy, selectElevator(_, _))
        .WillOnce(Return(elevator1));
    
    dispatcher->start();
    
    bool shutdownReceived = waitForShutdown(std::chrono::seconds(2));
    EXPECT_TRUE(shutdownReceived);       
    
    EXPECT_EQ(elevator1->getSnapshot().upStopsCount, 1);
}

TEST_F(GivenTestingElevatorDispatcherThreading, WhenDispatchLoopReceivesShutdownRequestThenCallsShutdownCallback) {
    InputRequest shutdownRequest(RequestType::SHUTDOWN_REQUEST);
    
    EXPECT_CALL(*mockQueue, try_pop())
        .WillOnce(Return(shutdownRequest));
    
    dispatcher->start();
    
    bool shutdownReceived = waitForShutdown(std::chrono::seconds(1));
    EXPECT_TRUE(shutdownReceived);
}