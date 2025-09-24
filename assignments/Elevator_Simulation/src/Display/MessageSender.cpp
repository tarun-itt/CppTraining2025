#include "Display/MessageSender.h"

MessageSender::MessageSender(IBlockingQueue<RenderRequest>* displayQueue)
    : displayQueue(displayQueue) {}

void MessageSender::sendError(const std::string& message) {
    sendMessage(message, MessageType::ERROR);
}

void MessageSender::sendWarning(const std::string& message) {
    sendMessage(message, MessageType::WARNING);
}

void MessageSender::sendNormal(const std::string& message) {
    sendMessage(message, MessageType::NORMAL);
}

void MessageSender::sendMessage(const std::string& message, MessageType type) {
    pushMessage(message, type, "system_message");
}

void MessageSender::pushMessage(const std::string& message, MessageType type, const std::string& messageId) {
    if (displayQueue) {
        auto messagePrintable = new MessagePrintable(message, type);
        RenderRequest request(RenderOperation::Display, messagePrintable, messageId);
        displayQueue->push(request);
    }
}