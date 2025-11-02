#pragma once

#include <string>
#include <iostream>

class IOHandler {
public:
    IOHandler() = default;

    std::string readLine();
    void write(const std::string &message);
    void writeLine(const std::string &message);
    void writeError(const std::string &error);

    void showPrompt(const std::string &currentPath);

private:
    std::istream &input = std::cin;
    std::ostream &output = std::cout;
    std::ostream &errorOutput = std::cerr;
};