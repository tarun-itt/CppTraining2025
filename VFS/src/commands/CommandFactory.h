#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "FileSystemNode.h"
#include "ICommand.h"
#include "IOutputHandler.h"

class CommandFactory {
  public:
    explicit CommandFactory(IOutputHandler &output);

    std::unique_ptr<ICommand> createCommand(const std::string &name) const;

    void setCommandDescriptions(const std::unordered_map<std::string, std::string> &descriptions) {
        commandDescriptions = descriptions;
    }

  private:
    IOutputHandler &output;
    std::unordered_map<std::string, std::string> commandDescriptions;
};