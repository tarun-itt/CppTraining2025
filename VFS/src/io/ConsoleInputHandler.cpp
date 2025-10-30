#include <iostream>

#include "ConsoleInputHandler.h"

ConsoleInputHandler::ConsoleInputHandler() : endOfInput(false) {}

std::string ConsoleInputHandler::readLine() {
    if (endOfInput)
        return "";

    std::string line;
    if (!std::getline(std::cin, line)) {
        endOfInput = true;
        return "";
    }

    return line;
}

bool ConsoleInputHandler::canReadInput() const {
    return !endOfInput;
}

void ConsoleInputHandler::setEndOfInput() {
    endOfInput = true;
}