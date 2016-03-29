//@@author A0125290M
#pragma once
#include "Command.h"
using namespace std;

class Command_Exit : public Command {
private:
	string _searchTerm;
	COMMAND_TYPE _commandType;
public:
	Command_Exit();
	COMMAND_TYPE getCommandType();
	string getStringForm();
	bool execute();
	bool undo();
};