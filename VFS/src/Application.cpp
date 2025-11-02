#include "../inc/Application.h"
#include "../inc/FileSystemPersistence.h"

Application::Application() : dataFilename("vfs_data.txt") { 
    initialize(); 
}

Application::Application(const std::string& dataFilename) : dataFilename(dataFilename) {
    initialize();
}

void Application::initialize() {
  auto persistenceImpl = createFilePersistence(dataFilename);
  fileSystem = std::make_unique<FileSystem>(std::move(persistenceImpl));

  ioHandler = std::make_unique<IOHandler>();
  parser = std::make_unique<CommandParser>();
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
    input = ioHandler->readLine();

    if (input == "EOF_REACHED") {
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

    ParsedCommand parsedCmd = parser->parse(input);
    commandHandler->execute(parsedCmd);
  }
}