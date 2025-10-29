#include <sstream>

#include "FileSystemManager.h"
#include "ListCommand.h"

ListCommand::ListCommand(IOutputHandler &output) : output(output) {}

CommandResult ListCommand::execute(const std::vector<std::string> &args, FileSystemManager &fs) {
    std::string targetPath = ".";
    if (!args.empty()) {
        targetPath = args[0];
    }

    std::shared_ptr<Directory> targetDir;
    if (targetPath == ".") {
        targetDir = fs.getCurrentDirectory();
    } else {
        targetDir = fs.getDirectory(targetPath);
    }

    if (!targetDir) {
        return CommandResult(CommandResultStatus::Failure, "Directory not found: " + targetPath);
    }

    const auto &children = targetDir->getChildren();
    if (!children.empty()) {
        for (const auto &child : children) {
            std::ostringstream line;
            line << (child->isDirectory() ? "d" : "-");
            line << " " << child->getName();
            line << " (" << child->getSize() << " bytes)";
            output.writeLine(line.str());
        }
    }

    return CommandResult(CommandResultStatus::Success);
}