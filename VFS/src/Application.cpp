#include "Application.h"
#include "FileSystemPersistence.h"

Application::Application() : dataFilename("vfs_data.txt") { 
    initialize(); 
}

Application::Application(const std::string& dataFilename) : dataFilename(dataFilename) {
    initialize();
}

void Application::initialize() {
  auto persistedFileSystem = std::make_unique<FileSystemPersistence>(dataFilename);
  fileSystem = std::make_unique<FileSystem>(std::move(persistedFileSystem));

  ioHandler = std::make_unique<IOHandler>();
  commandParser = std::make_unique<CommandParser>();
  commandHandler = std::make_unique<CommandHandler>(*fileSystem, *ioHandler);

  fileSystem->initialize();

  fileSystem->loadFileSystem();
}

void Application::run() {
  processCommands();
}

void Application::processCommands() {
  std::string input;

  while (true) {
    ioHandler->showPrompt(fileSystem->getCurrentPath());
    
    if (!ioHandler->readLine(input)) {
      fileSystem->saveFileSystem();
      break;
    }

    if (input == "exit" || input == "quit") {
      fileSystem->saveFileSystem();
      break;
    }

    if (input.empty()) {
      continue;
    }

    ParsedCommand parsedCmd = commandParser->parse(input);
    commandHandler->execute(parsedCmd);
  }
}