#include <iostream>
#include <string>

class Car {
private:
    std::string engineStatus;
    int speed;

    void changeEngineStatus(const std::string& status) {
        engineStatus = status;
    }

public:
    Car() : engineStatus("OFF"), speed(0) {}

    void start() {
        changeEngineStatus("ON");
        speed = 0;
        std::cout << "Car started.\n";
    }

    void accelerate(int increment) {
        if (engineStatus == "ON") {
            speed += increment;
            std::cout << "Accelerated to " << speed << " km/h.\n";
        } else {
            std::cout << "Can't accelerate. The engine is OFF.\n";
        }
    }

    void stop() {
        speed = 0;
        changeEngineStatus("OFF");
        std::cout << "Car stopped.\n";
    }

    int getSpeed() const {
        return speed;
    }
};

int main() {
    Car myCar;

    myCar.start();
    myCar.accelerate(50);
    std::cout << "Current speed: " << myCar.getSpeed() << " km/h\n";
    myCar.stop();

    return 0;
}
