#pragma once

#include <memory>
#include <string>
#include <vector>

class FileSystemManager;

enum class CommandResultStatus { Success, Failure, InvalidArguments };

struct CommandResult {
    CommandResultStatus status;
    std::string message;

    CommandResult(CommandResultStatus s, const std::string &msg = "") : status(s), message(msg) {}
};

class ICommand {
  public:
    virtual ~ICommand() = default;

    virtual CommandResult execute(const std::vector<std::string> &args, FileSystemManager &fs) = 0;
    virtual std::string getName() const = 0;
    virtual std::string getDescription() const = 0;
    virtual std::string getUsage() const = 0;
};