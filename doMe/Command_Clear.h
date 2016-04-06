//@@author A0125290M
#pragma once
#include "Command.h"
using namespace std;

class Command_Clear : public Command {
private:
	list<Task*> _oldTaskList;
	vector<int> _deleteList;
	Task* _deletedTask;
	CommandType _commandType;

	bool outOfRange();
	void clearAllTasks();
	void clearSelectedTasks();
public:
	Command_Clear(vector<int>* deleteList);
	bool execute();
	bool undo();
	vector<int>* getDeleteList();
	Task* getTask();
	CommandType getCommandType();
	string getStringForm();
};