#pragma once

#include <string>
#include <vector>

#include "CommandParser.h"

class FileSystem;
class IOHandler;

class CommandHandler {
public:
  explicit CommandHandler(FileSystem &fs, IOHandler &io);

  bool execute(const ParsedCommand &parsedCmd);

private:
  FileSystem &fs;
  IOHandler &io;

  bool executeCat(const std::vector<std::string> &args);
  bool executeCd(const std::vector<std::string> &args);
  bool executeEcho(const std::vector<std::string> &args);
  bool executeFind(const std::vector<std::string> &args);
  bool executeGrep(const std::vector<std::string> &args);
  bool executeHelp(const std::vector<std::string> &args);
  bool executeLs(const std::vector<std::string> &args);
  bool executeMkdir(const std::vector<std::string> &args);
  bool executeRm(const std::vector<std::string> &args);
  bool executeTouch(const std::vector<std::string> &args);

  void showHelp() const;
  void showCommandHelp(const std::string &command) const;
};