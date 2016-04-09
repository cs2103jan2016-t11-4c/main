//@@author A0125290M
#pragma once
#include "Command.h"
#include "Command_Invalid.h"
using namespace std;

class Command_Redo : public Command {
private:
	Command* _redoneCommand;
public:
	Command_Redo();
	//bool execute();
	//bool undo();
	void setRedoneCommand(Command* command);
	Command* getRedoneCommand();
	CommandType getCommandType();
	string getStringForm();
};