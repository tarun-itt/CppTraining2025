#include <algorithm>
#include <cctype>

#include "../inc/CommandParser.h"

ParsedCommand CommandParser::parse(const std::string &input) const {
    ParsedCommand result;
    result.isValid = false;

    std::vector<std::string> tokens = tokenize(input);
    
    if (tokens.empty()) {
        result.errorMessage = "No command entered";
        return result;
    }

    result.name = tokens[0];
    result.args = std::vector<std::string>(tokens.begin() + 1, tokens.end());

    if (!validateCommand(result.name)) {
        result.errorMessage = "Unknown command: " + result.name;
        return result;
    }

    if (!validateArguments(result.name, result.args)) {
        result.errorMessage = "Invalid arguments for command: " + result.name;
        return result;
    }

    result.isValid = true;
    return result;
}

std::vector<std::string> CommandParser::tokenize(const std::string &input) const {
    std::vector<std::string> tokens;
    std::string current;
    
    for (size_t i = 0; i < input.length(); ++i) {
        char c = input[i];
        
        if (std::isspace(c)) {
            if (!current.empty()) {
                tokens.push_back(current);
                current.clear();
            }
        } else if (c == '>') {
            if (!current.empty()) {
                tokens.push_back(current);
                current.clear();
            }
            
            if (i + 1 < input.length() && input[i + 1] == '>') {
                tokens.push_back(">>");
                i++;
            } else {
                tokens.push_back(">");
            }
        } else {
            current += c;
        }
    }
    
    if (!current.empty()) {
        tokens.push_back(current);
    }
    
    return tokens;
}

bool CommandParser::validateCommand(const std::string &commandName) const {
    static const std::vector<std::string> validCommands = {
        "cat", "cd", "echo", "find", "grep", "help", "ls", "mkdir", "pwd", "rm", "touch"
    };

    return std::find(validCommands.begin(), validCommands.end(), commandName) != validCommands.end();
}

bool CommandParser::validateArguments(const std::string &commandName, const std::vector<std::string> &args) const {
    if (commandName == "cat") return validateCatArgs(args);
    if (commandName == "cd") return validateCdArgs(args);
    if (commandName == "echo") return validateEchoArgs(args);
    if (commandName == "find") return validateFindArgs(args);
    if (commandName == "grep") return validateGrepArgs(args);
    if (commandName == "help") return args.size() <= 1;
    if (commandName == "ls") return validateLsArgs(args);
    if (commandName == "mkdir") return validateMkdirArgs(args);
    if (commandName == "pwd") return args.empty();
    if (commandName == "rm") return validateRmArgs(args);
    if (commandName == "touch") return validateTouchArgs(args);

    return false;
}

bool CommandParser::validateCatArgs(const std::vector<std::string> &args) const {
    if (args.size() == 1) {
        return true;
    }
    if (args.size() == 2 && args[0] == ">>") {
        return true;
    }
    return false;
}

bool CommandParser::validateCdArgs(const std::vector<std::string> &args) const {
    return args.size() <= 1;
}

bool CommandParser::validateEchoArgs(const std::vector<std::string> &args) const {
    if (args.empty()) return false;
    
    for (size_t i = 0; i < args.size(); ++i) {
        if (args[i] == ">>" || args[i] == ">") {
            return i + 1 < args.size();
        }
    }
    
    return true;
}

bool CommandParser::validateFindArgs(const std::vector<std::string> &args) const {
    if (args.empty()) return false;
    
    if (args[0] == "-name") return args.size() == 2;
    if (args[0] == "-size") return args.size() == 3 && isValidNumber(args[1]) && isValidNumber(args[2]);
    if (args[0] == "-time") return args.size() == 3 && isValidNumber(args[1]) && isValidNumber(args[2]);
    
    return false;
}

bool CommandParser::validateGrepArgs(const std::vector<std::string> &args) const {
    return args.size() == 2;
}

bool CommandParser::validateLsArgs(const std::vector<std::string> &args) const {
    return args.size() <= 1;
}

bool CommandParser::validateMkdirArgs(const std::vector<std::string> &args) const {
    return args.size() == 1;
}

bool CommandParser::validateRmArgs(const std::vector<std::string> &args) const {
    return args.size() == 1;
}

bool CommandParser::validateTouchArgs(const std::vector<std::string> &args) const {
    return args.size() == 1;
}

bool CommandParser::isValidPath(const std::string &path) const {
    if (path.empty()) return false;
    
    const std::string invalidChars = "<>:\"|?*";
    return path.find_first_of(invalidChars) == std::string::npos;
}

bool CommandParser::isValidNumber(const std::string &str) const {
    if (str.empty()) return false;
    
    for (char c : str) {
        if (!std::isdigit(c)) return false;
    }
    
    return true;
}