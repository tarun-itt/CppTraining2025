#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Elevator.h"
#include "mocks/MockElevatorSchedulingStrategy.h"

using ::testing::Return;

class GivenTestingElevator : public ::testing::Test {
protected:
    MockElevatorSchedulingStrategy* mockStrategy;
    Elevator* elevator;

    void SetUp() override {
        mockStrategy = new MockElevatorSchedulingStrategy();
        elevator = new Elevator(1, mockStrategy);
    }

    void TearDown() override {
        delete elevator;
        delete mockStrategy;
    }
};

TEST_F(GivenTestingElevator, WhenInstantiatedThenStateIsIdleAndAtGroundFloor) {
    auto snapshot = elevator->getSnapshot();
    EXPECT_EQ(snapshot.id, 1);
    EXPECT_EQ(snapshot.currentFloor, 0);
    EXPECT_EQ(snapshot.state, ElevatorState::IDLE);
}

TEST_F(GivenTestingElevator, WhenRequestIsAddedAboveThenUpStopsAreUpdated) {
    elevator->addRequest(2, 5);
    auto snapshot = elevator->getSnapshot();
    EXPECT_EQ(snapshot.upStopsCount, 1);
    EXPECT_EQ(snapshot.downStopsCount, 0);
}

TEST_F(GivenTestingElevator, WhenRequestIsAddedBelowThenDownStopsAreUpdated) {
    elevator->addRequest(-1, -2);
    auto snapshot = elevator->getSnapshot();
    EXPECT_EQ(snapshot.downStopsCount, 1);
    EXPECT_EQ(snapshot.upStopsCount, 0);
}

TEST_F(GivenTestingElevator, WhenRequestIsAddedAtCurrentFloorThenDestinationIsAddedDirectly) {
    elevator->addRequest(0, 5);
    auto snapshot = elevator->getSnapshot();
    EXPECT_EQ(snapshot.upStopsCount, 1);
    EXPECT_EQ(snapshot.downStopsCount, 0);
}

TEST_F(GivenTestingElevator, WhenGetSnapshotCalledThenReturnsAccurateState) {
    elevator->addRequest(3, 8);
    elevator->addRequest(1, -2);

    auto snapshot = elevator->getSnapshot();
    EXPECT_EQ(snapshot.id, 1);
    EXPECT_EQ(snapshot.currentFloor, 0);
    EXPECT_EQ(snapshot.upStopsCount, 2);
    EXPECT_EQ(snapshot.downStopsCount, 0);
}