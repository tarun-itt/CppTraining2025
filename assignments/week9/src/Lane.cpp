#include "Lane.h"

Lane::Lane(int id, const std::string& name, int cars)
    : id(id), name(name), remainingCars(cars), initialCars(cars) {}

bool Lane::hasCars() const {
    return remainingCars > 0;
}

bool Lane::processCar() {
    if (remainingCars > 0) {
        --remainingCars;
        return true;
    }
    return false;
}

const std::string& Lane::getName() const {
    return name;
}

int Lane::getRemainingCarCount() const {
    return remainingCars;
}

int Lane::getInitialCarCount() const {
    return initialCars;
}