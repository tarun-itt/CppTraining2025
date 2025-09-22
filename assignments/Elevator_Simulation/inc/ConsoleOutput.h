#ifndef CONSOLEOUTPUT_H
#define CONSOLEOUTPUT_H

#include <string>
#include <thread>
#include <atomic>
#include <unordered_map>
#include <mutex>

#include "IOutputProcessor.h"
#include "Printable.h"
#include "IBlockingQueue.h"

class ConsoleOutput : public IOutputProcessor {
public:
    ConsoleOutput(IBlockingQueue<RenderRequest>* queue);
    ~ConsoleOutput();

    void start() override;
    void stop() override;
    bool isRunning() const override;

private:
    void displayLoop();
    void initialize();
    void cleanup();
    void display(const Printable& object);
    void clearScreen();
    std::string getColorCode(ConsoleColor color, bool background) const;


    struct ActiveRenderObject {
        Printable* object = nullptr;
        std::chrono::steady_clock::time_point creationTime;
    };
    
    std::atomic<bool> running;
    std::thread outputThread;
    IBlockingQueue<RenderRequest>* renderObjects;
    std::unordered_map<std::string, ActiveRenderObject> displayedObjects;
    std::mutex displayMutex;
};

#endif