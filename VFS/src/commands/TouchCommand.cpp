#include "TouchCommand.h"
#include "FileSystemManager.h"

TouchCommand::TouchCommand(IOutputHandler &output) : output(output) {}

CommandResult TouchCommand::execute(const std::vector<std::string> &args, FileSystemManager &fs) {
    if (args.empty()) {
        return CommandResult(CommandResultStatus::InvalidArguments, "Usage: touch <filename>");
    }

    const std::string &fileName = args[0];

    if (fs.createFile(fileName)) {
        return CommandResult(CommandResultStatus::Success);
    } else {
        return CommandResult(CommandResultStatus::Failure, "Failed to create file: " + fileName);
    }
}