#ifndef TIMER_H
#define TIMER_H

#include "ITimer.h"

class Timer : public ITimer {
    public:
        void sleep(int seconds) override;
};

#endif
