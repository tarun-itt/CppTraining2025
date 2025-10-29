#include "CommandFactory.h"
#include "CatCommand.h"
#include "ChangeDirectoryCommand.h"
#include "EchoCommand.h"
#include "FindCommand.h"
#include "GrepCommand.h"
#include "HelpCommand.h"
#include "ListCommand.h"
#include "MakeDirectoryCommand.h"
#include "PrintWorkingDirectoryCommand.h"
#include "RemoveCommand.h"
#include "TouchCommand.h"

CommandFactory::CommandFactory(IOutputHandler &output) : output(output) {}

std::unique_ptr<ICommand> CommandFactory::createCommand(const std::string &name) const {
    if (name == "ls" || name == "list") {
        return std::unique_ptr<ICommand>(new ListCommand(output));
    } else if (name == "cd") {
        return std::unique_ptr<ICommand>(new ChangeDirectoryCommand(output));
    } else if (name == "pwd") {
        return std::unique_ptr<ICommand>(new PrintWorkingDirectoryCommand(output));
    } else if (name == "mkdir") {
        return std::unique_ptr<ICommand>(new MakeDirectoryCommand(output));
    } else if (name == "touch") {
        return std::unique_ptr<ICommand>(new TouchCommand(output));
    } else if (name == "rm") {
        return std::unique_ptr<ICommand>(new RemoveCommand(output));
    } else if (name == "cat") {
        return std::unique_ptr<ICommand>(new CatCommand(output));
    } else if (name == "echo") {
        return std::unique_ptr<ICommand>(new EchoCommand(output));
    } else if (name == "find") {
        return std::unique_ptr<ICommand>(new FindCommand(output));
    } else if (name == "grep") {
        return std::unique_ptr<ICommand>(new GrepCommand(output));
    } else if (name == "help") {
        return std::unique_ptr<ICommand>(new HelpCommand(output, commandDescriptions));
    }

    return nullptr;
}