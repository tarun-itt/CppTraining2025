#pragma once

#include "ICommand.h"
#include "IOutputHandler.h"

class EchoCommand : public ICommand {
  public:
    explicit EchoCommand(IOutputHandler &output);

    CommandResult execute(const std::vector<std::string> &args, FileSystemManager &fs) override;
    std::string getName() const override { return "echo"; }
    std::string getDescription() const override { return "Display arguments"; }
    std::string getUsage() const override { return "echo <text> >> <filename>"; }

  private:
    IOutputHandler &output;
};