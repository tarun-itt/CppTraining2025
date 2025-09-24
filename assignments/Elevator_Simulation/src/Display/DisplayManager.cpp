#include "Display/DisplayManager.h"

IBlockingQueue<RenderRequest>* DisplayManager::messages = nullptr;

void DisplayManager::initialize(IBlockingQueue<RenderRequest>* queue) {
    messages = queue;
}

void DisplayManager::shutdown() {
    messages = nullptr;
}

void DisplayManager::display(IPrintable* object, const std::string& id) {
    if (messages && !id.empty()) {
        messages->push(RenderRequest(RenderOperation::Display, object, id));
    }
}

void DisplayManager::remove(const std::string& id) {
    if (messages && !id.empty()) {
        messages->push(RenderRequest(RenderOperation::Remove, nullptr, id));
    }
}

void DisplayManager::clear() {
    if (messages) {
        messages->push(RenderRequest(RenderOperation::Clear, nullptr, ""));
    }
}