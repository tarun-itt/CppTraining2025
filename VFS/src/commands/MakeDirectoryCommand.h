#pragma once

#include "ICommand.h"
#include "IOutputHandler.h"

class MakeDirectoryCommand : public ICommand {
	public:
		explicit MakeDirectoryCommand(IOutputHandler &output);

		CommandResult execute(const std::vector<std::string> &args, FileSystemManager &fs) override;
		std::string getName() const override { return "mkdir"; }
		std::string getDescription() const override { return "Create directory"; }
		std::string getUsage() const override { return "mkdir <directory>"; }

	private:
		IOutputHandler &output;
};