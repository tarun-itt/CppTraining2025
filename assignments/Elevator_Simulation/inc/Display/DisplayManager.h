#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include "Display/IPrintable.h"
#include "Display/RenderRequest.h"
#include "Interfaces/IBlockingQueue.h"

class DisplayManager {
public:
    static void initialize(IBlockingQueue<RenderRequest>* queue);
    static void shutdown();
    static void display(IPrintable* object, const std::string& id);
    static void remove(const std::string& id);
    static void clear();

private:
    static IBlockingQueue<RenderRequest>* messages;
};

#endif