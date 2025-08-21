#include "UserTurtleService.h"


void UserTurtleService::drawSquare(int sideLength) {
    turtle->PenDown();
    for (int i = 0; i < 4; i++) {
        turtle->Forward(sideLength);
        turtle->Turn(90);
    }
}