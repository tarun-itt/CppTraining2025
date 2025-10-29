#pragma once

#include "ICommand.h"
#include "IOutputHandler.h"

class FindCommand : public ICommand {
  public:
    explicit FindCommand(IOutputHandler &output);

    CommandResult execute(const std::vector<std::string> &args, FileSystemManager &fs) override;
    std::string getName() const override { return "find"; }
    std::string getDescription() const override { return "Find files"; }
    std::string getUsage() const override { return "find <pattern>"; }

  private:
    IOutputHandler &output;
};