#pragma once

#include "ICommand.h"
#include "IOutputHandler.h"

class GrepCommand : public ICommand {
  public:
    explicit GrepCommand(IOutputHandler &output);

    CommandResult execute(const std::vector<std::string> &args, FileSystemManager &fs) override;
    std::string getName() const override { return "grep"; }
    std::string getDescription() const override { return "Search for text in files"; }
    std::string getUsage() const override { return "grep <pattern> <filename>"; }

  private:
    IOutputHandler &output;
};