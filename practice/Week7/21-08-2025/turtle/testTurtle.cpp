#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "MockTurtle.h"
#include "UserTurtleService.h"


class TurtleTest : public ::testing::Test {
protected:
    MockTurtle mock;
};

TEST_F(TurtleTest, MovesForward) {
    EXPECT_CALL(mock, Forward(10)).Times(4); 
    EXPECT_CALL(mock, PenDown()).Times(1);
    EXPECT_CALL(mock, Turn(90)).Times(4);     
    
    UserTurtleService service(&mock);
    service.drawSquare(10);
}

TEST_F(TurtleTest, GoesToCoordinates) {
    EXPECT_CALL(mock, GoTo(5, 7)).Times(1);
    mock.GoTo(5, 7);
}
