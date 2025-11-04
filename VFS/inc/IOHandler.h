#pragma once

#include <iostream>
#include <string>

class IOHandler {
public:
  IOHandler() = default;

  bool readLine(std::string &line);
  void write(const std::string &message);
  void writeLine(const std::string &message);

  void showPrompt(const std::string &currentPath);

private:
  std::istream &input = std::cin;
  std::ostream &output = std::cout;

  constexpr static const char *EOF_MARKER = "<<EOF>>";
};