#include <gtest/gtest.h>
#include "../inc/Lane.h"

class GivenTestingLane : public ::testing::Test {
protected:
    int emptyLaneId;
    int multiCarLaneId;
    int zeroCars;
    int multipleCars;
    std::string emptyLaneName;
    std::string multiCarLaneName;

    Lane* emptyLane;
    Lane* multiCarLane;

    void SetUp() override {
        emptyLaneId = 1;
        multiCarLaneId = 2;
        zeroCars = 0;
        multipleCars = 5;
        emptyLaneName = "A";
        multiCarLaneName = "B";

        emptyLane = new Lane(emptyLaneId, emptyLaneName, zeroCars);
        multiCarLane = new Lane(multiCarLaneId, multiCarLaneName, multipleCars);
    }

    void TearDown() override {
        delete emptyLane;
        delete multiCarLane;
    }
};

TEST_F(GivenTestingLane, WhenConstructorCalled_ThenLaneInitializedCorrectly) {
    EXPECT_EQ(multiCarLane->getName(), multiCarLaneName);
    EXPECT_EQ(multiCarLane->getInitialCarCount(), multipleCars);
    EXPECT_EQ(multiCarLane->getRemainingCarCount(), multipleCars);
    EXPECT_TRUE(multiCarLane->hasCars());
}

TEST_F(GivenTestingLane, WhenConstructorCalledWithZeroCars_ThenLaneHasNoCars) {
    EXPECT_EQ(emptyLane->getInitialCarCount(), zeroCars);
    EXPECT_EQ(emptyLane->getRemainingCarCount(), zeroCars);
    EXPECT_FALSE(emptyLane->hasCars());
}

TEST_F(GivenTestingLane, WhenProcessCarCalled_ThenCarCountDecreases) {
    EXPECT_TRUE(multiCarLane->processCar());
    EXPECT_EQ(multiCarLane->getRemainingCarCount(), multipleCars - 1);
}

TEST_F(GivenTestingLane, WhenProcessCarCalledOnEmptyLane_ThenReturnsFalse) {
    EXPECT_FALSE(emptyLane->processCar());
}

TEST_F(GivenTestingLane, WhenGetInitialCarCountCalled_ThenReturnsOriginalCount) {
    EXPECT_EQ(multiCarLane->getInitialCarCount(), multipleCars);
    multiCarLane->processCar(); //to decrease car count
    EXPECT_EQ(multiCarLane->getInitialCarCount(), multipleCars);
}