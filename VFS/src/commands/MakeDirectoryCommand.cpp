#include "MakeDirectoryCommand.h"
#include "FileSystemManager.h"

MakeDirectoryCommand::MakeDirectoryCommand(IOutputHandler &output) : output(output) {}

CommandResult MakeDirectoryCommand::execute(const std::vector<std::string> &args, FileSystemManager &fs) {
  if (args.empty()) {
    return CommandResult(CommandResultStatus::InvalidArguments, "Usage: mkdir <directory>");
  }

  const std::string &dirName = args[0];

  if (fs.createDirectory(dirName)) {
    return CommandResult(CommandResultStatus::Success);
  } else {
    return CommandResult(CommandResultStatus::Failure, "Failed to create directory: " + dirName);
  }
}