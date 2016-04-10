//@@author A0125290M
#pragma once
#include "Command.h"
using namespace std;

class Command_Scroll : public Command {
public:
	Command_Scroll();
	CommandType getCommandType();
	string getStringForm();
};