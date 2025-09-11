#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <thread>
#include "../inc/TrafficController.h"
#include "mocks/mockLane.h"
#include "mocks/mockTimer.h"

using ::testing::Return;
using ::testing::AtLeast;

class GivenTestingTrafficController : public ::testing::Test {
protected:
    int firstGreenLightDuration;
    int secondGreenLightDuration;
    int sleepDurationZero;
    int sleepDurationOne;
    int zeroCars;
    int multipleCars;
    std::string laneNameA;
    std::string laneNameB;
    
    MockLane* mockLaneA;
    MockLane* mockLaneB;
    MockTimer* mockTimer;
    std::vector<ILane*> lanes;
    TrafficController* trafficController;

    void SetUp() override {
        sleepDurationZero = 0;
        sleepDurationOne = 1;
        firstGreenLightDuration = 2;
        secondGreenLightDuration = 5;
        zeroCars = 0;
        multipleCars = 3;
        laneNameA = "A";
        laneNameB = "B";
        
        mockLaneA = new MockLane();
        mockLaneB = new MockLane();
        mockTimer = new MockTimer();
        
        lanes.push_back(mockLaneA);
        lanes.push_back(mockLaneB);
    }

    void TearDown() override {
        delete trafficController;
        delete mockLaneA;
        delete mockLaneB;
        delete mockTimer;
    }
};

TEST_F(GivenTestingTrafficController, WhenConstructorCalled_ThenControllerInitialized) {
    EXPECT_NO_THROW({
        trafficController = new TrafficController(lanes, *mockTimer, firstGreenLightDuration);
    });
}

TEST_F(GivenTestingTrafficController, WhenRunCalledWithNoCars_ThenSimulationEndsQuickly) {
    ON_CALL(*mockLaneA, hasCars()).WillByDefault(Return(false));
    ON_CALL(*mockLaneB, hasCars()).WillByDefault(Return(false));
    ON_CALL(*mockLaneA, getRemainingCarCount()).WillByDefault(Return(zeroCars));
    ON_CALL(*mockLaneB, getRemainingCarCount()).WillByDefault(Return(zeroCars));
    
    trafficController = new TrafficController(lanes, *mockTimer, firstGreenLightDuration);
    trafficController->run();
}

TEST_F(GivenTestingTrafficController, WhenRunCalledWithCars_ThenLanesProcessCars) {
    int remainingCarsA = multipleCars;
    
    ON_CALL(*mockLaneA, hasCars()).WillByDefault([&remainingCarsA]() { return remainingCarsA > 0; });
    ON_CALL(*mockLaneA, getRemainingCarCount()).WillByDefault([&remainingCarsA]() { return remainingCarsA; });
    ON_CALL(*mockLaneA, processCar()).WillByDefault([&remainingCarsA]() { 
        if (remainingCarsA > 0) {
            remainingCarsA--;
            return true;
        }
        return false;
    });
    ON_CALL(*mockLaneA, getName()).WillByDefault(testing::ReturnRef(laneNameA));
    ON_CALL(*mockLaneA, getInitialCarCount()).WillByDefault(Return(multipleCars));
    
    ON_CALL(*mockLaneB, hasCars()).WillByDefault(Return(false));
    ON_CALL(*mockLaneB, getRemainingCarCount()).WillByDefault(Return(zeroCars));
    
    EXPECT_CALL(*mockTimer, sleep(sleepDurationOne)).Times(AtLeast(1));
    for (auto* lane : lanes) {
        auto* mockLane = dynamic_cast<MockLane*>(lane);
        if(mockLane->hasCars()) {
            EXPECT_CALL(*mockLane, processCar()).Times(AtLeast(1));
        }
    }   
    
    
    trafficController = new TrafficController(lanes, *mockTimer, firstGreenLightDuration);
    trafficController->run();
}

TEST_F(GivenTestingTrafficController, WhenMultipleLanesHaveCars_ThenOnlyActiveLaneProcesses) {
    int initialCarsA = 2;
    int remainingCarsA = initialCarsA;
    int initialCarsB = 1;
    int remainingCarsB = initialCarsB;
    
    ON_CALL(*mockLaneA, hasCars()).WillByDefault([&remainingCarsA]() { return remainingCarsA > 0; });
    ON_CALL(*mockLaneA, getRemainingCarCount()).WillByDefault([&remainingCarsA]() { return remainingCarsA; });
    ON_CALL(*mockLaneA, processCar()).WillByDefault([&remainingCarsA]() { 
        if (remainingCarsA > 0) {
            remainingCarsA--;
            return true;
        }
        return false;
    });
    ON_CALL(*mockLaneA, getInitialCarCount()).WillByDefault(Return(initialCarsA));
    
    ON_CALL(*mockLaneB, hasCars()).WillByDefault([&remainingCarsB]() { return remainingCarsB > 0; });
    ON_CALL(*mockLaneB, getRemainingCarCount()).WillByDefault([&remainingCarsB]() { return remainingCarsB; });
    ON_CALL(*mockLaneB, processCar()).WillByDefault([&remainingCarsB]() { 
        if (remainingCarsB > 0) {
            remainingCarsB--;
            return true;
        }
        return false;
    });
    ON_CALL(*mockLaneB, getInitialCarCount()).WillByDefault(Return(initialCarsB));
    
    EXPECT_CALL(*mockTimer, sleep(sleepDurationOne)).Times(AtLeast(1));
    EXPECT_CALL(*mockLaneA, processCar()).Times(AtLeast(1));
    EXPECT_CALL(*mockLaneB, processCar()).Times(AtLeast(1));
    
    trafficController = new TrafficController(lanes, *mockTimer, firstGreenLightDuration);
    
    std::thread controllerThread([this]() {
        trafficController->run();
    });
    
    controllerThread.join();
}
