//@@author A0125290M
#pragma once
#include "Command.h"
using namespace std;

class Command_Delete : public Command {
private:
	Task* _task;
	int _index;

	bool outOfRange();
public:
	Command_Delete(int index);
	bool execute();
	bool undo();
	Task* getTask();
	COMMAND_TYPE getCommandType();
};