#pragma once

#include <unordered_map>

#include "ICommand.h"
#include "IOutputHandler.h"

class HelpCommand : public ICommand {
  public:
    explicit HelpCommand(IOutputHandler &output);
    // New ctor that receives command descriptions (key -> short description)
    HelpCommand(IOutputHandler &output, const std::unordered_map<std::string, std::string> &descriptions);

    CommandResult execute(const std::vector<std::string> &args, FileSystemManager &fs) override;
    std::string getName() const override { return "help"; }
    std::string getDescription() const override { return "Display help information"; }
    std::string getUsage() const override { return "help"; }

  private:
    IOutputHandler &output;
    const std::unordered_map<std::string, std::string> *descriptions = nullptr;
};