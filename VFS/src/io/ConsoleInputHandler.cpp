#include <iostream>

#include "ConsoleInputHandler.h"

ConsoleInputHandler::ConsoleInputHandler() : endOfInput(false) {}

std::string ConsoleInputHandler::readLine(const std::string &prompt) {
    if (endOfInput)
        return "";

    if (!prompt.empty()) {
        std::cout << prompt;
        std::cout.flush();
    }

    std::string line;
    if (!std::getline(std::cin, line)) {
        endOfInput = true;
        return "";
    }

    return line;
}

bool ConsoleInputHandler::hasInput() const {
    return !endOfInput;
}

void ConsoleInputHandler::setEndOfInput() {
    endOfInput = true;
}