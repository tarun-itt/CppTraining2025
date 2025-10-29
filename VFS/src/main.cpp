#include <iostream>
#include <memory>

#include "CommandFactory.h"
#include "CommandRegistry.h"
#include "ConsoleInputHandler.h"
#include "ConsoleOutputHandler.h"
#include "FilePersistenceStrategy.h"
#include "FileSystemManager.h"

int main() {
    try {
        auto output = std::make_shared<ConsoleOutputHandler>();
        auto input = std::make_shared<ConsoleInputHandler>();

        auto persistence =
            std::unique_ptr<FilePersistenceStrategy>(new FilePersistenceStrategy("vfs_data.bin", *output));

        FileSystemManager fs(std::move(persistence));

        CommandFactory factory(*output);
        CommandRegistry registry(factory, *output);
        registry.registerAllCommands();

        factory.setCommandDescriptions(registry.getCommandDescriptions());

        while (input->hasInput()) {
            std::string prompt = fs.getCurrentPath() + " $ ";
            std::string line = input->readLine(prompt);

            if (line.empty())
                continue;

            if (line == "exit" || line == "quit") {
                break;
            }

            auto result = registry.executeCommand(line, fs);

            if (result.status == CommandResultStatus::Failure) {
                output->writeError(result.message);
            } else if (result.status == CommandResultStatus::InvalidArguments) {
                output->writeError(result.message);
            } else if (!result.message.empty()) {
                output->writeLine(result.message);
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}