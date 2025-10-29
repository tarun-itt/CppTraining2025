#pragma once

#include <string>

#include "IInputHandler.h"

class ConsoleInputHandler : public IInputHandler {
  public:
    ConsoleInputHandler();

    std::string readLine(const std::string &prompt = "") override;
    bool hasInput() const override;
    void setEndOfInput() override;

  private:
    bool endOfInput;
};