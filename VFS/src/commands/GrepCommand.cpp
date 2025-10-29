#include "GrepCommand.h"
#include "FileSystemManager.h"

GrepCommand::GrepCommand(IOutputHandler &output) : output(output) {}

CommandResult GrepCommand::execute(const std::vector<std::string> &args, FileSystemManager &fs) {
    if (args.empty()) {
        return CommandResult(CommandResultStatus::InvalidArguments, "Usage: " + getUsage());
    }

    const std::string &pattern = args[0];

    auto lines = fs.searchLines(pattern);

    if (lines.empty()) {
        output.writeLine("No matches found for pattern: " + pattern);
        return CommandResult(CommandResultStatus::Success);
    }

    for (const auto &line : lines) {
        output.writeLine(line);
    }

    return CommandResult(CommandResultStatus::Success);
}