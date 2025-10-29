#pragma once

#include "ICommand.h"
#include "IOutputHandler.h"

class RemoveCommand : public ICommand {
	public:
		explicit RemoveCommand(IOutputHandler &output);

		CommandResult execute(const std::vector<std::string> &args, FileSystemManager &fs) override;
		std::string getName() const override { return "rm"; }
		std::string getDescription() const override { return "Remove file or directory"; }
		std::string getUsage() const override { return "rm <file_or_directory>"; }

	private:
		IOutputHandler &output;
};