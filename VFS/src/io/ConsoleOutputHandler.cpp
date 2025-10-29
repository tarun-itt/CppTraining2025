#include <iostream>

#include "ConsoleOutputHandler.h"

ConsoleOutputHandler::ConsoleOutputHandler() {}

void ConsoleOutputHandler::write(const std::string &text) {
    std::cout << text;
    std::cout.flush();
}

void ConsoleOutputHandler::writeLine(const std::string &text) {
    std::cout << text << std::endl;
}

void ConsoleOutputHandler::writeError(const std::string &error) {
    std::cerr << "Error: " << error << std::endl;
}