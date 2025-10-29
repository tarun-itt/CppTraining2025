#include "CatCommand.h"
#include "Directory.h"
#include "File.h"
#include "FileSystemManager.h"

CatCommand::CatCommand(IOutputHandler &output) : output(output) {}

CommandResult CatCommand::execute(const std::vector<std::string> &args, FileSystemManager &fs) {
    if (args.empty()) {
        return CommandResult(CommandResultStatus::InvalidArguments, "Usage: cat <filename>");
    }

    const std::string &fileName = args[0];
    std::string content = fs.readFile(fileName);

    if (content.empty() && !fs.exists(fileName)) {
        return CommandResult(CommandResultStatus::Failure, "File not found: " + fileName);
    }

    output.write(content);
    return CommandResult(CommandResultStatus::Success);
}