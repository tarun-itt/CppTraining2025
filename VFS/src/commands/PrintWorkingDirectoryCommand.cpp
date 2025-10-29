#include "PrintWorkingDirectoryCommand.h"
#include "FileSystemManager.h"

PrintWorkingDirectoryCommand::PrintWorkingDirectoryCommand(IOutputHandler &output) : output(output) {}

CommandResult PrintWorkingDirectoryCommand::execute(const std::vector<std::string> &args, FileSystemManager &fs) {
    output.writeLine(fs.getCurrentPath());
    return CommandResult(CommandResultStatus::Success);
}