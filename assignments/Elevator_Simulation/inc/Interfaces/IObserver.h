#ifndef I_OBSERVER_H
#define I_OBSERVER_H

class IObserver {
public:
    virtual ~IObserver() = default;

    virtual void onStateChanged() = 0;
};

#endif