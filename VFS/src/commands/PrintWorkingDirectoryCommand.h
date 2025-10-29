#pragma once

#include "ICommand.h"
#include "IOutputHandler.h"

class PrintWorkingDirectoryCommand : public ICommand {
  public:
    explicit PrintWorkingDirectoryCommand(IOutputHandler &output);

    CommandResult execute(const std::vector<std::string> &args, FileSystemManager &fs) override;
    std::string getName() const override { return "pwd"; }
    std::string getDescription() const override { return "Print working directory"; }
    std::string getUsage() const override { return "pwd"; }

  private:
    IOutputHandler &output;
};