#ifndef ITIMER_H
#define ITIMER_H

class ITimer {
public:
    virtual ~ITimer() {}
    virtual void sleep(int seconds) = 0;
};

#endif