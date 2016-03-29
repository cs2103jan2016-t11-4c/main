//@@author A0125290M
#pragma once
#include "Command.h"
using namespace std;

class Command_Clear : public Command {
private:
	list<Task*> _oldTaskList;
	vector<int> _deleteList;

	bool outOfRange();
public:
	Command_Clear(vector<int>* deleteList);
	bool execute();
	bool undo();
	COMMAND_TYPE getCommandType();
	string getStringForm();
};