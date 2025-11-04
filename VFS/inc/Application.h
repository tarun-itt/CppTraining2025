#pragma once

#include <memory>

#include "FileSystem.h"
#include "CommandHandler.h"
#include "CommandParser.h"
#include "IOHandler.h"
#include "FileSystemPersistence.h"

class Application {
public:
    Application();
    explicit Application(const std::string& dataFilename);
    ~Application() = default;

    void run();

private:
    std::unique_ptr<FileSystem> fileSystem;
    std::unique_ptr<IOHandler> ioHandler;
    std::unique_ptr<CommandParser> commandParser;
    std::unique_ptr<CommandHandler> commandHandler;
    std::string dataFilename;

    void initialize();
    void processCommands();
};