#include <sstream>

#include "EchoCommand.h"
#include "FileSystemManager.h"

EchoCommand::EchoCommand(IOutputHandler &output) : output(output) {}

CommandResult EchoCommand::execute(const std::vector<std::string> &args, FileSystemManager &fs) {
    if (args.size() < 3 || args[args.size() - 2] != ">") {
        return CommandResult(CommandResultStatus::InvalidArguments, "Usage: echo <text> > <filename>");
    }

    std::string fileName = args.back();
    std::ostringstream content;

    for (size_t i = 0; i < args.size() - 2; ++i) {
        if (i > 0)
            content << " ";
        content << args[i];
    }

    if (fs.writeFile(fileName, content.str())) {
        return CommandResult(CommandResultStatus::Success);
    } else {
        return CommandResult(CommandResultStatus::Failure, "Failed to write to file: " + fileName);
    }
}