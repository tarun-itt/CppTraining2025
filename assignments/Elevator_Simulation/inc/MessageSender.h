#ifndef MESSAGE_SENDER_H
#define MESSAGE_SENDER_H

#include <string>
#include "MessagePrintable.h"
#include "IBlockingQueue.h"

class MessageSender {
public:
    explicit MessageSender(IBlockingQueue<RenderRequest>* displayQueue);
    
    void sendError(const std::string& message);
    void sendWarning(const std::string& message);
    void sendNormal(const std::string& message);
    void sendMessage(const std::string& message, MessageType type);

private:
    IBlockingQueue<RenderRequest>* displayQueue;
    void pushMessage(const std::string& message, MessageType type, const std::string& messageId);
};

#endif