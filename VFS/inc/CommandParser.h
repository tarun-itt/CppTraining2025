#pragma once

#include <string>
#include <vector>

struct ParsedCommand {
    std::string name;
    std::vector<std::string> args;
    bool isValid;
    std::string errorMessage;
};

class CommandParser {
public:
    CommandParser() = default;

    ParsedCommand parse(const std::string &input) const;

private:
    bool validateCommand(const std::string &commandName) const;
    bool validateArguments(const std::string &commandName, const std::vector<std::string> &args) const;
    
    std::vector<std::string> tokenize(const std::string &input) const;
    bool isValidPath(const std::string &path) const;
    bool isValidNumber(const std::string &str) const;
    
    bool validateCatArgs(const std::vector<std::string> &args) const;
    bool validateCdArgs(const std::vector<std::string> &args) const;
    bool validateEchoArgs(const std::vector<std::string> &args) const;
    bool validateFindArgs(const std::vector<std::string> &args) const;
    bool validateGrepArgs(const std::vector<std::string> &args) const;
    bool validateLsArgs(const std::vector<std::string> &args) const;
    bool validateMkdirArgs(const std::vector<std::string> &args) const;
    bool validateRmArgs(const std::vector<std::string> &args) const;
    bool validateTouchArgs(const std::vector<std::string> &args) const;
};