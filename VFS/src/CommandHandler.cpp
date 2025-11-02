#include <unordered_map>

#include "../inc/CommandHandler.h"
#include "../inc/FileSystem.h"
#include "../inc/IOHandler.h"

CommandHandler::CommandHandler(FileSystem &fs, IOHandler &io) : fs(fs), io(io) {}

bool CommandHandler::execute(const ParsedCommand &parsedCmd) {
    if (!parsedCmd.isValid) {
        io.writeError(parsedCmd.errorMessage);
        return false;
    }

    const std::string &command = parsedCmd.name;
    const std::vector<std::string> &args = parsedCmd.args;

    if (command == "cat") {
        return executeCat(args);
    } else if (command == "cd") {
        return executeCd(args);
    } else if (command == "echo") {
        return executeEcho(args);
    } else if (command == "find") {
        return executeFind(args);
    } else if (command == "grep") {
        return executeGrep(args);
    } else if (command == "help") {
        return executeHelp(args);
    } else if (command == "ls") {
        return executeLs(args);
    } else if (command == "mkdir") {
        return executeMkdir(args);
    } else if (command == "pwd") {
        return executePwd(args);
    } else if (command == "rm") {
        return executeRm(args);
    } else if (command == "touch") {
        return executeTouch(args);
    } else {
        io.writeError("Unknown command: " + command);
        return false;
    }
}

bool CommandHandler::executeCat(const std::vector<std::string> &args) {
    if (args.empty()) {
        io.writeError("cat: missing file operand");
        return false;
    }
    
    if (args.size() >= 2 && args[0] == ">>") {
        std::string filename = args[1];
        
        io.writeLine("Entering interactive input mode. Type 'EOF' on a new line to finish.");
        std::string content;
        std::string line;
        
        while (true) {
            line = io.readLine();
            if (line == "EOF_REACHED" || line == "EOF") {
                break;
            }
            content += line + "\n";
        }
        
        if (!fs.exists(filename)) {
            fs.createFile(filename, content);
        } else {
            fs.appendToFile(filename, content);
        }
        
        io.writeLine("Content appended to " + filename);
        return true;
    }
    
    const std::string &filename = args[0];
    
    if (!fs.exists(filename)) {
        io.writeError("File not found: " + filename);
        return false;
    }

    auto file = fs.getFile(filename);
    if (!file) {
        io.writeError("Not a file: " + filename);
        return false;
    }

    std::string content = file->getContent();
    if (!content.empty()) {
        if (content.back() == '\n') {
            content.pop_back();
        }
        io.writeLine(content);
    }
    return true;
}

bool CommandHandler::executeCd(const std::vector<std::string> &args) {
    std::string path = args.empty() ? "/" : args[0];
    
    if (!fs.changeDir(path)) {
        io.writeError("Cannot change directory to: " + path);
        return false;
    }
    
    return true;
}

bool CommandHandler::executeEcho(const std::vector<std::string> &args) {
    if (args.empty()) {
        io.writeLine("");
        return true;
    }
    
    enum class RedirectionType { NONE, APPEND, WRITE };
    RedirectionType redirectType = RedirectionType::NONE;
    std::string filename;
    std::vector<std::string> textArgs;
    
    for (size_t i = 0; i < args.size(); ++i) {
        if (args[i] == ">>") {
            redirectType = RedirectionType::APPEND;
            if (i + 1 < args.size()) {
                filename = args[i + 1];
                break;
            }
        } else if (args[i] == ">") {
            redirectType = RedirectionType::WRITE;
            if (i + 1 < args.size()) {
                filename = args[i + 1];
                break;
            }
        } else {
            textArgs.push_back(args[i]);
        }
    }
    
    std::string output;
    for (size_t i = 0; i < textArgs.size(); ++i) {
        if (i > 0) output += " ";
        output += textArgs[i];
    }
    
    if (redirectType == RedirectionType::APPEND && !filename.empty()) {
        if (!fs.exists(filename)) {
            fs.createFile(filename, output + "\n");
        } else {
            fs.appendToFile(filename, output + "\n");
        }
        return true;
    } else if (redirectType == RedirectionType::WRITE && !filename.empty()) {
        if (!fs.exists(filename)) {
            fs.createFile(filename, output + "\n");
        } else {
            fs.writeFile(filename, output + "\n");
        }
        return true;
    } else {
        io.writeLine(output);
        return true;
    }
}

bool CommandHandler::executeFind(const std::vector<std::string> &args) {
    std::vector<std::shared_ptr<FileSystemComponent>> results;
    
    if (args[0] == "-name") {
        results = fs.findByName(args[1]);
    } else if (args[0] == "-size") {
        size_t minSize = std::stoul(args[1]);
        size_t maxSize = std::stoul(args[2]);
        results = fs.findBySize(minSize, maxSize);
    } else if (args[0] == "-time") {
        time_t startTime = std::stol(args[1]);
        time_t endTime = std::stol(args[2]);
        results = fs.findByTimestamp(startTime, endTime);
    }

    for (const auto &item : results) {
        io.writeLine(item->getName());
    }
    
    return true;
}

bool CommandHandler::executeGrep(const std::vector<std::string> &args) {
    const std::string &pattern = args[0];
    const std::string &filename = args[1];
    
    if (!fs.exists(filename)) {
        io.writeError("File not found: " + filename);
        return false;
    }

    auto file = fs.getFile(filename);
    if (!file) {
        io.writeError("Not a file: " + filename);
        return false;
    }

    auto lines = file->searchLines(pattern);
    for (const std::string &line : lines) {
        io.writeLine(line);
    }
    
    return true;
}

bool CommandHandler::executeHelp(const std::vector<std::string> &args) {
    if (args.empty()) {
        showHelp();
    } else {
        showCommandHelp(args[0]);
    }
    return true;
}

bool CommandHandler::executeLs(const std::vector<std::string> &args) {
    std::shared_ptr<Directory> dir;
    
    if (args.empty()) {
        dir = fs.getCurrentDirectory();
    } else {
        dir = fs.getDirectory(args[0]);
        if (!dir) {
            io.writeError("Directory not found: " + args[0]);
            return false;
        }
    }

    auto children = dir->getChildren();
    for (const auto &child : children) {
        std::string prefix = child->isDirectory() ? "d " : "f ";
        io.writeLine(prefix + child->getName());
    }
    
    return true;
}

bool CommandHandler::executeMkdir(const std::vector<std::string> &args) {
    const std::string &dirname = args[0];
    
    if (!fs.createDirectory(dirname)) {
        io.writeError("Cannot create directory: " + dirname);
        return false;
    }
    
    return true;
}

bool CommandHandler::executePwd([[maybe_unused]] const std::vector<std::string> &args) {
    io.writeLine(fs.getCurrentPath());
    return true;
}

bool CommandHandler::executeRm(const std::vector<std::string> &args) {
    const std::string &filename = args[0];
    
    if (!fs.exists(filename)) {
        io.writeError("File not found: " + filename);
        return false;
    }

    auto obj = fs.getObject(filename);
    if (obj->isDirectory()) {
        if (!fs.removeDir(filename)) {
            io.writeError("Cannot remove directory: " + filename);
            return false;
        }
    } else {
        if (!fs.removeFile(filename)) {
            io.writeError("Cannot remove file: " + filename);
            return false;
        }
    }
    
    return true;
}

bool CommandHandler::executeTouch(const std::vector<std::string> &args) {
    const std::string &filename = args[0];
    
    if (!fs.createFile(filename)) {
        io.writeError("Cannot create file: " + filename);
        return false;
    }
    
    return true;
}

void CommandHandler::showHelp() const {
    io.writeLine("Available commands:");
    io.writeLine("  cat <file>       - Display file content");
    io.writeLine("  cd [path]        - Change directory");
    io.writeLine("  echo <text>      - Display text");
    io.writeLine("  find <options>   - Find files/directories");
    io.writeLine("  grep <pattern> <file> - Search pattern in file");
    io.writeLine("  help [command]   - Show help");
    io.writeLine("  ls [path]        - List directory contents");
    io.writeLine("  mkdir <dir>      - Create directory");
    io.writeLine("  pwd              - Show current directory");
    io.writeLine("  rm <file>        - Remove file/directory");
    io.writeLine("  touch <file>     - Create empty file");
}

void CommandHandler::showCommandHelp(const std::string &command) const {
    static const std::unordered_map<std::string, std::string> helpTexts = {
        {"cat", "cat <file> - Display the contents of a file"},
        {"cd", "cd [path] - Change current directory. If no path given, goes to root"},
        {"echo", "echo <text...> - Display the provided text"},
        {"find", "find <options> - Find files. Options: -name <pattern>, -size <min> <max>, -time <start> <end>"},
        {"grep", "grep <pattern> <file> - Search for pattern in file and display matching lines"},
        {"help", "help [command] - Show general help or help for specific command"},
        {"ls", "ls [path] - List contents of directory. If no path given, lists current directory"},
        {"mkdir", "mkdir <dirname> - Create a new directory"},
        {"pwd", "pwd - Display current working directory path"},
        {"rm", "rm <file> - Remove a file or directory"},
        {"touch", "touch <filename> - Create a new empty file"}
    };

    auto it = helpTexts.find(command);
    if (it != helpTexts.end()) {
        io.writeLine(it->second);
    } else {
        io.writeError("No help available for command: " + command);
    }
}