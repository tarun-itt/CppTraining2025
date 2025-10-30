#include <sstream>

#include "EchoCommand.h"
#include "FileSystemManager.h"

EchoCommand::EchoCommand(IOutputHandler &output) : output(output) {}

CommandResult EchoCommand::execute(const std::vector<std::string> &args, FileSystemManager &fs) {
    if (args.size() < 3) {
        return CommandResult(CommandResultStatus::InvalidArguments, "Usage: " + getUsage());
    }

    bool append = false;
    size_t redirectIndex = 0;

    for (size_t i = 0; i < args.size(); ++i) {
        if (args[i] == ">>") {
            redirectIndex = i;
            append = (args[i] == ">>");
            break;
        }
    }

    if (redirectIndex != args.size() - 2) {
        return CommandResult(CommandResultStatus::InvalidArguments, "Usage: " + getUsage());
    }

    std::string fileName = args.back();
    std::ostringstream content;

    for (size_t i = 0; i < redirectIndex; ++i) {
        if (i > 0)
            content << " ";
        content << args[i];
    }
    content << "\n";
    bool success = append
        ? fs.appendToFile(fileName, content.str())
        : fs.writeFile(fileName, content.str());

    if (success)
        return CommandResult(CommandResultStatus::Success);
    else
        return CommandResult(CommandResultStatus::Failure, "Failed to write to file: " + fileName);
}
