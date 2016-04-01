//@@author A0125290M
#pragma once
#include "Command.h"
using namespace std;

class Command_Invalid : public Command {
public:
	Command_Invalid();
	CommandType getCommandType();
	string getStringForm();
	bool execute();

};