#include <algorithm>

#include "FileSystemManager.h"
#include "HelpCommand.h"

HelpCommand::HelpCommand(IOutputHandler &output) : output(output) {}

HelpCommand::HelpCommand(IOutputHandler &output, const std::unordered_map<std::string, std::string> &descriptions)
    : output(output), descriptions(&descriptions) {}

CommandResult HelpCommand::execute(const std::vector<std::string> &args, FileSystemManager &) {
    if (descriptions && !descriptions->empty()) {
        std::vector<std::pair<std::string, std::string>> items(descriptions->begin(), descriptions->end());
        std::sort(items.begin(), items.end(),
                  [](const std::pair<std::string, std::string> &a, const std::pair<std::string, std::string> &b) {
                      return a.first < b.first;
                  });
        for (const auto &p : items) {
            output.writeLine(p.first + " - " + p.second);
        }
    }

    return CommandResult(CommandResultStatus::Success);
}