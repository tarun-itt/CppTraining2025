#pragma once

#include <iostream>

#include "IOutputHandler.h"

class ConsoleOutputHandler : public IOutputHandler {
  public:
    ConsoleOutputHandler();

    void write(const std::string &text) override;
    void writeLine(const std::string &text) override;
    void writeError(const std::string &error) override;
};