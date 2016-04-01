//@@author A0125290M
#pragma once
#include "Command.h"
using namespace std;

class Command_Add : public Command {
private:
	Task* _task;
public:
	Command_Add(Task* task);
	bool execute();
	bool undo();
	Task* getTask();
	CommandType getCommandType();
	string getStringForm();
};