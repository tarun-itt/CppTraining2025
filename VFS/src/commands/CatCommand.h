#pragma once

#include "ICommand.h"
#include "IOutputHandler.h"

class CatCommand : public ICommand {
  public:
    explicit CatCommand(IOutputHandler &output);

    CommandResult execute(const std::vector<std::string> &args, FileSystemManager &fs) override;
    std::string getName() const override { return "cat"; }
    std::string getDescription() const override { return "Display file contents"; }
    std::string getUsage() const override { return "cat <filename>"; }

  private:
    IOutputHandler &output;
};