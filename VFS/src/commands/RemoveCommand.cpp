#include "RemoveCommand.h"
#include "FileSystemManager.h"

RemoveCommand::RemoveCommand(IOutputHandler &output) : output(output) {}

CommandResult RemoveCommand::execute(const std::vector<std::string> &args, FileSystemManager &fs) {
  if (args.empty()) {
    return CommandResult(CommandResultStatus::InvalidArguments, "Usage: rm <file_or_directory>");
  }

  const std::string &targetName = args[0];

  if (fs.remove(targetName)) {
    return CommandResult(CommandResultStatus::Success);
  } else {
    return CommandResult(CommandResultStatus::Failure, "Failed to remove: " + targetName);
  }
}