#include "ChangeDirectoryCommand.h"
#include "FileSystemManager.h"

ChangeDirectoryCommand::ChangeDirectoryCommand(IOutputHandler &output) : output(output) {}

CommandResult ChangeDirectoryCommand::execute(const std::vector<std::string> &args, FileSystemManager &fs) {
    if (args.empty()) {
        return CommandResult(CommandResultStatus::InvalidArguments, "Usage: cd <directory>");
    }

    const std::string &targetPath = args[0];

    if (fs.changeDirectory(targetPath)) {
        return CommandResult(CommandResultStatus::Success);
    } else {
        return CommandResult(CommandResultStatus::Failure, "Directory not found: " + targetPath);
    }
}