#ifndef MESSAGE_PRINTABLE_H
#define MESSAGE_PRINTABLE_H

#include <string>
#include <chrono>

#include "Printable.h"

enum class MessageType {
    ERROR,
    WARNING,
    NORMAL
};

class MessagePrintable : public Printable {
public:
    MessagePrintable(const std::string& message, MessageType type, Position position = {100, 2 });
    
    std::string getContent() const override;
    DisplayProperties getDisplayProperties() const override;

private:
    std::string message;
    MessageType type;
    Position position;
    ConsoleColor getColorForType(MessageType type) const;
};

#endif