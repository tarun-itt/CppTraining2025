#pragma once

#include "ICommand.h"
#include "IOutputHandler.h"

class ListCommand : public ICommand {
  public:
    explicit ListCommand(IOutputHandler &output);

    CommandResult execute(const std::vector<std::string> &args, FileSystemManager &fs) override;
    std::string getName() const override { return "ls"; }
    std::string getDescription() const override { return "List directory contents"; }
    std::string getUsage() const override { return "ls [directory]"; }

  private:
    IOutputHandler &output;
};