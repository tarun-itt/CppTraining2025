#include <iostream>

#include "../inc/IOHandler.h"

std::string IOHandler::readLine() {
    std::string line;
    if (std::getline(input, line)) {
        return line;
    }
    return "EOF_REACHED";
}

void IOHandler::write(const std::string &message) {
    output << message;
    output.flush();
}

void IOHandler::writeLine(const std::string &message) {
    output << message << std::endl;
}

void IOHandler::writeError(const std::string &error) {
    errorOutput << "Error: " << error << std::endl;
}

void IOHandler::showPrompt(const std::string &currentPath) {
    output << currentPath << "$ ";
    output.flush();
}