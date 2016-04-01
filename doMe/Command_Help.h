//@@author A0125290M
#pragma once
#include "Command.h"
using namespace std;

class Command_Help : public Command {
public:
	Command_Help();
	bool execute();
	CommandType getCommandType();
	string getStringForm();
};