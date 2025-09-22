#include <gtest/gtest.h>
#include "../inc/ScanSchedulingStrategy.h"

class GivenTestingScanSchedulingStrategy : public ::testing::Test {
protected:
    ScanSchedulingStrategy strategy;
    std::set<int> upStops;
    std::set<int> downStops;
};

TEST_F(GivenTestingScanSchedulingStrategy, WhenMovingUpWithUpStopsThenSelectsClosestUpStop) {
    upStops = {5, 8};
    int nextStop = strategy.findNextStop(3, Direction::UP, upStops, downStops);
    EXPECT_EQ(nextStop, 5);
}

TEST_F(GivenTestingScanSchedulingStrategy, WhenMovingUpWithNoMoreUpStopsThenReversesToHighestDownStop) {
    upStops = {5, 8};
    downStops = {2, 4};
    int nextStop = strategy.findNextStop(9, Direction::UP, upStops, downStops);
    EXPECT_EQ(nextStop, 4);
}

TEST_F(GivenTestingScanSchedulingStrategy, WhenMovingDownWithDownStopsThenSelectsClosestDownStop) {
    downStops = {1, 4};
    int nextStop = strategy.findNextStop(6, Direction::DOWN, upStops, downStops);
    EXPECT_EQ(nextStop, 4);
}

TEST_F(GivenTestingScanSchedulingStrategy, WhenMovingDownWithNoMoreDownStopsThenReversesToLowestUpStop) {
    downStops = {1, 4};
    upStops = {6, 9};
    int nextStop = strategy.findNextStop(0, Direction::DOWN, upStops, downStops);
    EXPECT_EQ(nextStop, 6);
}

TEST_F(GivenTestingScanSchedulingStrategy, WhenIdleWithOnlyUpStopsThenSelectsLowestUpStop) {
    upStops = {3, 7};
    int nextStop = strategy.findNextStop(0, Direction::IDLE, upStops, downStops);
    EXPECT_EQ(nextStop, 3);
}

TEST_F(GivenTestingScanSchedulingStrategy, WhenIdleWithOnlyDownStopsThenSelectsHighestDownStop) {
    downStops = {1, 4};
    int nextStop = strategy.findNextStop(8, Direction::IDLE, upStops, downStops);
    EXPECT_EQ(nextStop, 4);
}

TEST_F(GivenTestingScanSchedulingStrategy, WhenNoStopsThenReturnsCurrentFloor) {
    int nextStop = strategy.findNextStop(5, Direction::IDLE, upStops, downStops);
    EXPECT_EQ(nextStop, 5);
}