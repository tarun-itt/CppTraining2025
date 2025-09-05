#ifndef ILANE_H
#define ILANE_H

#include <string>

class ILane {
public:
    virtual ~ILane() = default;

    virtual const std::string& getName() const = 0;
    virtual bool hasCars() const = 0;
    virtual bool processCar() = 0;
    virtual int getRemainingCarCount() const = 0;
    virtual int getInitialCarCount() const = 0;
};

#endif