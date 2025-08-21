#include "turtleInterface.h"

class UserTurtleService {
    ITurtle* turtle;

public:
    UserTurtleService(ITurtle* turtle) : turtle(turtle) {}

    void drawSquare(int sideLength);
        
    ~UserTurtleService() {
    }
};