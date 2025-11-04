#include <cstdio>
#include <iostream>

#include "IOHandler.h"

bool IOHandler::readLine(std::string &line) {
  std::getline(input, line);
  return !line.empty() && line != EOF_MARKER;
}

void IOHandler::write(const std::string &message) {
  output << message;
  output.flush();
}

void IOHandler::writeLine(const std::string &message) {
  output << message << std::endl;
}

void IOHandler::showPrompt(const std::string &currentPath) {
  output << currentPath << "$ ";
  output.flush();
}