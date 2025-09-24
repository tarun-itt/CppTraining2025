#include <iostream>
#include <chrono>
#include <vector>
#include <sstream>

#include "Display/ConsoleOutput.h"

const auto FRAME_DURATION = std::chrono::milliseconds(33);

ConsoleOutput::ConsoleOutput(IBlockingQueue<RenderRequest>* queue)
    : running(false), renderObjects(queue) {}

ConsoleOutput::~ConsoleOutput() {
    stop();
}

void ConsoleOutput::start() {
    if (running.load()) return;
    initialize();
    running.store(true);
    outputThread = std::thread(&ConsoleOutput::displayLoop, this);
}

void ConsoleOutput::stop() {
    if (!running.load()) return;
    running.store(false);
    if (outputThread.joinable()) {
        outputThread.join();
    }
    cleanup();
}

bool ConsoleOutput::isRunning() const {
    return running.load();
}

void ConsoleOutput::displayLoop() {
    while (running.load()) {
        auto frameStartTime = std::chrono::steady_clock::now();
        RenderRequest request;
        while ((request = renderObjects->try_pop()).operationType != RenderOperation::None) {
            std::lock_guard<std::mutex> lock(displayMutex);
            
            switch (request.operationType) {
                case RenderOperation::Display:
                    if (request.object && !request.printableId.empty()) {
                        if (!displayedObjects.count(request.printableId)) {
                            displayedObjects[request.printableId] = { request.object, std::chrono::steady_clock::now() };
                        }
                        else {
                            displayedObjects[request.printableId].object = request.object;
                        }
                    }
                    break;
                case RenderOperation::Remove:
                    if (!request.printableId.empty() && displayedObjects.count(request.printableId)) {
                        delete displayedObjects[request.printableId].object;
                        displayedObjects.erase(request.printableId);
                    }
                    break;
                case RenderOperation::Clear:
                    for (auto& pair : displayedObjects) {
                        delete pair.second.object;
                    }
                    displayedObjects.clear();
                    break;
                default:
                    break;
            }
        }

        std::vector<std::string> expiredObjectIds;
        {
            std::lock_guard<std::mutex> lock(displayMutex); 
            for (const auto& component : displayedObjects) {
                const auto& activeObject = component.second;
                if (activeObject.object->getDisplayProperties().displayDuration > std::chrono::milliseconds(0)) {
                    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(frameStartTime - activeObject.creationTime);
                    if (elapsed >= activeObject.object->getDisplayProperties().displayDuration) {
                        expiredObjectIds.push_back(component.first);
                    }
                }
            }
        }
        
        if (!expiredObjectIds.empty()) {
            std::lock_guard<std::mutex> lock(displayMutex);
            for (const auto& id : expiredObjectIds) {
                if (displayedObjects.count(id)) {
                    delete displayedObjects[id].object;
                    displayedObjects.erase(id);
                }
            }
        }
        
        {
            std::lock_guard<std::mutex> lock(displayMutex);
            clearScreen();
            
            for (const auto& pair : displayedObjects) {
                if (pair.second.object) {
                    display(*pair.second.object); 
                }
            }
        }


        auto frameEndTime = std::chrono::steady_clock::now();
        auto frameElapsed = frameEndTime - frameStartTime;
        if (frameElapsed < FRAME_DURATION) {
            std::this_thread::sleep_for(FRAME_DURATION - frameElapsed);
        }
    }
}

void ConsoleOutput::initialize() {
    std::cout << "\033[?25l" << std::flush;
    std::cout << "\033[2J\033[H" << std::flush;
}

void ConsoleOutput::cleanup() {
    std::lock_guard<std::mutex> lock(displayMutex);
    for (auto& pair : displayedObjects) {
        delete pair.second.object;
    }
    displayedObjects.clear();

    std::cout << "\033[0m";
    std::cout << "\033[?25h";
    std::cout << "\033[2J\033[H" << std::flush;
}

void ConsoleOutput::clearScreen() {
    std::cout << "\033[2J\033[H";
}

void ConsoleOutput::display(const IPrintable& object) {
    const auto props = object.getDisplayProperties();
    const std::string content = object.getContent();
    std::stringstream ss(content);
    std::string line;

    int currentRow = props.position.y;

    while (std::getline(ss, line)) {
        std::cout << "\033[" << (currentRow + 1) << ";" << (props.position.x + 1) << "H";

        if (props.bold) std::cout << "\033[1m";
        std::cout << getColorCode(props.backgroundColor, true);
        std::cout << getColorCode(props.foregroundColor, false);

        std::cout << line;
        std::cout << "\033[0m" << std::flush;

        currentRow++;
    }
}



std::string ConsoleOutput::getColorCode(ConsoleColor color, bool background) const {
    int code = static_cast<int>(color);
    if (code == 0) return "";
    return "\033[" + std::to_string(code + (background ? 10 : 0)) + "m";
}