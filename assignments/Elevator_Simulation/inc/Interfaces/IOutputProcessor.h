#ifndef IOUTPUTPROCESSOR_H
#define IOUTPUTPROCESSOR_H

class IOutputProcessor {
public:
    virtual ~IOutputProcessor() = default;

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual bool isRunning() const = 0;
};

#endif