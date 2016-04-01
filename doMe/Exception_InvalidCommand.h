//@@author A0125290M

#pragma once

#include "Command.h"
using namespace std;

class Command;

class Exception_InvalidCommand {
private:
	Command* _command;
public:
	Exception_InvalidCommand(Command* command);
	Command* getCommand();	
};