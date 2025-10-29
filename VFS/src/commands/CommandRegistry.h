#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "CommandFactory.h"
#include "ICommand.h"
#include "IOutputHandler.h"

class CommandRegistry {
  public:
    CommandRegistry(const CommandFactory &factory, IOutputHandler &output);

    void registerAllCommands();
    CommandResult executeCommand(const std::string &commandLine, FileSystemManager &fs);
    std::vector<std::string> getAvailableCommands() const;
    std::string getCommandHelp(const std::string &commandName) const;
    const std::unordered_map<std::string, std::string> &getCommandDescriptions() const { return commandDescriptions; }

  private:
    const CommandFactory &factory;
    IOutputHandler &output;
    std::unordered_map<std::string, std::string> commandDescriptions;

    std::vector<std::string> parseCommandLine(const std::string &commandLine) const;
};