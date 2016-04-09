//@@author A0125290M
#pragma once
#include "Command.h"
using namespace std;

class Command_Edit : public Command {
private:
	int _index;
	CommandType _commandType;
	vector<int> _editList;
	vector<Task> _oldTaskList;
	vector<Task*> _edittedTaskPtrList;

	static const int DATE_NO_CHANGE;
	static const int TIME_NO_CHANGE;
	static const string LOCATION_NO_CHANGE;

	string _newName;
	int _newDate1;
	int _newDate2;
	int _newTime1;
	int _newTime2;
	string _newLocation;
	int _newDoneStatus;

	bool outOfRange();
	bool isDeleteTaskParametersCommand();
	void editAllTasks();
	void editSelectedTasks();
public:
	Command_Edit(vector<int>* editList, Task* task);
	bool execute();
	bool undo();
	Task* getTask();
	vector<int>* getEditList();
	CommandType getCommandType();
    int getDoneStatus();
	string getStringForm();
};