//@@author A0125290M
#pragma once
#include "Command.h"
using namespace std;

class Command_Exit : public Command {
private:
	string _searchTerm;
public:
	Command_Exit();
	COMMAND_TYPE getCommandType();
	bool execute();
	bool undo();
	string getStringForm();
};