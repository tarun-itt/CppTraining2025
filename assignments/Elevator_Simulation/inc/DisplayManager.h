#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include "Printable.h"
#include "IBlockingQueue.h"

class DisplayManager {
public:
    static void initialize(IBlockingQueue<RenderRequest>* queue);
    static void shutdown();
    static void display(Printable* object, const std::string& id);
    static void remove(const std::string& id);
    static void clear();

private:
    static IBlockingQueue<RenderRequest>* messages;
};

#endif