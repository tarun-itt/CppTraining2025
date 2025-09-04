#ifndef LANE_H
#define LANE_H

#include "ILane.h"

class Lane : public ILane {
private:
    int id;
    std::string name;
    int remainingCars;
    int initialCars;

public:
    Lane(int id, const std::string& name, int cars);

    const std::string& getName() const override;
    bool hasCars() const override;
    bool processCar() override;
    int getRemainingCarCount() const override;
    int getInitialCarCount() const override;
};

#endif