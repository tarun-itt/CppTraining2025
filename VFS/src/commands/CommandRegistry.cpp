#include <algorithm>
#include <sstream>

#include "CommandRegistry.h"
#include "FileSystemManager.h"

CommandRegistry::CommandRegistry(const CommandFactory &factory, IOutputHandler &output)
    : factory(factory), output(output) {}

void CommandRegistry::registerAllCommands() {
    commandDescriptions["ls"] = "List directory contents";
    commandDescriptions["list"] = "List directory contents";
    commandDescriptions["cd"] = "Change directory";
    commandDescriptions["pwd"] = "Print working directory";
    commandDescriptions["mkdir"] = "Create directory";
    commandDescriptions["touch"] = "Create file";
    commandDescriptions["rm"] = "Remove file or directory";
    commandDescriptions["cat"] = "Display file contents";
    commandDescriptions["echo"] = "Write text to file";
    commandDescriptions["find"] = "Search for files";
    commandDescriptions["grep"] = "Search file contents";
    commandDescriptions["help"] = "Show available commands";
}

CommandResult CommandRegistry::executeCommand(const std::string &commandLine, FileSystemManager &fs) {
    auto tokens = parseCommandLine(commandLine);
    if (tokens.empty()) {
        return CommandResult(CommandResultStatus::InvalidArguments, "No command provided");
    }

    std::string commandName = tokens[0];
    std::vector<std::string> args(tokens.begin() + 1, tokens.end());

    auto command = factory.createCommand(commandName);
    if (!command) {
        return CommandResult(CommandResultStatus::Failure, "Unknown command: " + commandName);
    }

    return command->execute(args, fs);
}

std::vector<std::string> CommandRegistry::parseCommandLine(const std::string &commandLine) const {
    std::vector<std::string> tokens;
    std::istringstream stream(commandLine);
    std::string token;

    while (stream >> token) {
        tokens.push_back(token);
    }

    return tokens;
}