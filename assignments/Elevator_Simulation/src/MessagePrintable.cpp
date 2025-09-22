#include "MessagePrintable.h"

MessagePrintable::MessagePrintable(const std::string& message, MessageType type, Position position)
    : message(message), type(type), position(position) {}

std::string MessagePrintable::getContent() const {
    return message;
}

DisplayProperties MessagePrintable::getDisplayProperties() const {
    ConsoleColor color = getColorForType(type);
    return { 
        position,         
        color,               
        ConsoleColor::Black, 
        true,               
        std::chrono::milliseconds(3000)
    };
}

ConsoleColor MessagePrintable::getColorForType(MessageType type) const {
    switch (type) {
        case MessageType::ERROR:
            return ConsoleColor::Red;
        case MessageType::WARNING:
            return ConsoleColor::Yellow;
        case MessageType::NORMAL:
            return ConsoleColor::White;
        default:
            return ConsoleColor::White;
    }
}