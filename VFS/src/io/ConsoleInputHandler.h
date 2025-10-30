#pragma once

#include <string>

#include "IInputHandler.h"

class ConsoleInputHandler : public IInputHandler {
  public:
    ConsoleInputHandler();

    std::string readLine() override;
    bool canReadInput() const override;
    void setEndOfInput() override;

  private:
    bool endOfInput;
};