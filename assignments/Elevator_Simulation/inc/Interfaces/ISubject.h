#ifndef I_SUBJECT_H
#define I_SUBJECT_H

class IObserver;

class ISubject {
public:
    virtual ~ISubject() = default;

    virtual void addObserver(IObserver* observer) = 0;
    virtual void removeObserver(IObserver* observer) = 0;
    virtual void notifyObservers() = 0;
};

#endif