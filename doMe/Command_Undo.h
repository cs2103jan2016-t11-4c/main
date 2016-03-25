//@@author A0125290M
#pragma once
#include "Command.h"
using namespace std;

class Command_Undo : public Command {
private:
	Command* _undoneCommand;
public:
	Command_Undo();
	bool execute();
	bool undo();
	void setUndoneCommand(Command* command);
	Command* getUndoneCommand();
	COMMAND_TYPE getCommandType();
};