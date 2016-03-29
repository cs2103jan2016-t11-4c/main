//@@author A0125290M
#pragma once
#include "Command.h"
using namespace std;

class Command_Invalid : public Command {
public:
	Command_Invalid();
	COMMAND_TYPE getCommandType();
	string getStringForm();
	bool execute();

};