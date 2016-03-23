//@@author A0125290M
#pragma once
#include "Command.h"
using namespace std;

class Command_Undo : public Command {
public:
	Command_Undo();
	bool execute();
	bool undo();
	COMMAND_TYPE getCommandType();
};