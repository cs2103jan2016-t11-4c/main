//@@author A0125290M
#pragma once
#include "Command.h"
using namespace std;

class Command_Clear : public Command {
#ifndef TESTMODE
public:
#else
private:
#endif
	list<Task*> _oldTaskList;
	vector<int> _deleteList;
	Task* _deletedTask;
	CommandType _commandType;

	static const int LAST_ADDED_TASK_INDEX;

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