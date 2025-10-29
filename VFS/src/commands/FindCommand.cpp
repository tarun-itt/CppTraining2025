#include "FindCommand.h"
#include "FileSystemManager.h"

FindCommand::FindCommand(IOutputHandler &output) : output(output) {}

CommandResult FindCommand::execute(const std::vector<std::string> &args, FileSystemManager &fs) {
    if (args.empty()) {
        return CommandResult(
            CommandResultStatus::InvalidArguments,
            "Usage: find <pattern> | find -name <pattern> | find -size <min>:<max> | find -time <start>:<end>");
    }

    std::vector<std::shared_ptr<FileSystemObject>> results;

    try {
        if (args[0] == "-name") {
            if (args.size() < 2) {
                return CommandResult(CommandResultStatus::InvalidArguments, "Usage: find -name <pattern>");
            }
            results = fs.findByName(args[1]);

        } else if (args[0] == "-size") {
            if (args.size() < 2) {
                return CommandResult(CommandResultStatus::InvalidArguments, "Usage: find -size <min>:<max>");
            }
            const std::string &range = args[1];
            auto pos = range.find(':');
            if (pos == std::string::npos) {
                return CommandResult(CommandResultStatus::InvalidArguments, "Usage: find -size <min>:<max>");
            }
            size_t minSize = static_cast<size_t>(std::stoull(range.substr(0, pos)));
            size_t maxSize = static_cast<size_t>(std::stoull(range.substr(pos + 1)));
            results = fs.findBySize(minSize, maxSize);

        } else if (args[0] == "-time") {
            if (args.size() < 2) {
                return CommandResult(CommandResultStatus::InvalidArguments,
                                     "Usage: find -time <start>:<end> (epoch seconds)");
            }
            const std::string &range = args[1];
            auto pos = range.find(':');
            if (pos == std::string::npos) {
                return CommandResult(CommandResultStatus::InvalidArguments,
                                     "Usage: find -time <start>:<end> (epoch seconds)");
            }
            time_t start = static_cast<time_t>(std::stoll(range.substr(0, pos)));
            time_t end = static_cast<time_t>(std::stoll(range.substr(pos + 1)));
            results = fs.findByTimestamp(start, end);

        } else {
            const std::string &pattern = args[0];
            results = fs.findByName(pattern);
        }
    } catch (const std::exception &ex) {
        return CommandResult(CommandResultStatus::InvalidArguments, std::string("Invalid arguments: ") + ex.what());
    }

    if (results.empty()) {
        output.writeLine("No files found.");
        return CommandResult(CommandResultStatus::Success);
    }

    for (const auto &obj : results) {
        output.writeLine(obj->getName());
    }

    return CommandResult(CommandResultStatus::Success);
}