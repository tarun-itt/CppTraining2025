#pragma once

#include "ICommand.h"
#include "IOutputHandler.h"

class ChangeDirectoryCommand : public ICommand {
  public:
    explicit ChangeDirectoryCommand(IOutputHandler &output);

    CommandResult execute(const std::vector<std::string> &args, FileSystemManager &fs) override;
    std::string getName() const override { return "cd"; }
    std::string getDescription() const override { return "Change directory"; }
    std::string getUsage() const override { return "cd <directory>"; }

  private:
    IOutputHandler &output;
};