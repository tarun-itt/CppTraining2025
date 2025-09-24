#include <gtest/gtest.h>

#include "../inc/InputValidation.h"
#include "../inc/ElevatorSystemConfig.h"

class GivenTestingInputValidation : public ::testing::Test {
protected:
    ElevatorSystemConfig config;
    
    void SetUp() override {
        config = ElevatorSystemConfig();
        config.numberOfElevators = 2;
        config.numberOfFloors = 8;
        config.numberOfBasements = 2;
    }
};

TEST_F(GivenTestingInputValidation, WhenValidFloorRequestThenReturnsValid) {
    auto result = InputValidation::validate("f5 f1", config);
    ASSERT_TRUE(result.isValid);
    EXPECT_EQ(result.request.requestedAtFloor, 5);
    EXPECT_EQ(result.request.targetFloors[0], 1);
    EXPECT_EQ(result.request.direction, Direction::DOWN);
}

TEST_F(GivenTestingInputValidation, WhenValidBasementRequestThenReturnsValid) {
    auto result = InputValidation::validate("b2 g", config);
    ASSERT_TRUE(result.isValid);
    EXPECT_EQ(result.request.requestedAtFloor, -2);
    EXPECT_EQ(result.request.targetFloors[0], 0);
    EXPECT_EQ(result.request.direction, Direction::UP);
}

TEST_F(GivenTestingInputValidation, WhenExitCommandThenReturnsShutdownRequest) {
    auto result = InputValidation::validate("exit", config);
    ASSERT_TRUE(result.isValid);
    EXPECT_TRUE(result.request.isShutdown());
}

TEST_F(GivenTestingInputValidation, WhenQuitCommandThenReturnsShutdownRequest) {
    auto result = InputValidation::validate("quit", config);
    ASSERT_TRUE(result.isValid);
    EXPECT_TRUE(result.request.isShutdown());
}

TEST_F(GivenTestingInputValidation, WhenSameFloorThenReturnsInvalid) {
    auto result = InputValidation::validate("f4 f4", config);
    ASSERT_FALSE(result.isValid);
}

TEST_F(GivenTestingInputValidation, WhenInvalidFloorStringThenReturnsInvalid) {
    auto result = InputValidation::validate("fx g", config);
    ASSERT_FALSE(result.isValid);
    EXPECT_EQ(result.errorMessage, "Invalid from floor: fx");
}

TEST_F(GivenTestingInputValidation, WhenInvalidFormatThenReturnsInvalid) {
    auto result = InputValidation::validate("f1f5", config);
    ASSERT_FALSE(result.isValid);
}