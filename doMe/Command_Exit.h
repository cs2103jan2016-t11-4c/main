//@@author A0125290M
#pragma once
#include "Command.h"
using namespace std;

class Command_Exit : public Command {
private:
	string _searchTerm;
	CommandType _commandType;
public:
	Command_Exit();
	CommandType getCommandType();
	string getStringForm();
	bool execute();
	bool undo();
};