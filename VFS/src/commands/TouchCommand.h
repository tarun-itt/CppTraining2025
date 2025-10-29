#pragma once

#include "ICommand.h"
#include "IOutputHandler.h"

class TouchCommand : public ICommand {
	public:
		explicit TouchCommand(IOutputHandler &output);

		CommandResult execute(const std::vector<std::string> &args, FileSystemManager &fs) override;
		std::string getName() const override { return "touch"; }
		std::string getDescription() const override { return "Create file"; }
		std::string getUsage() const override { return "touch <filename>"; }

	private:
		IOutputHandler &output;
};