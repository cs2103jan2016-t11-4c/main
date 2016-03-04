#pragma once
#include <list>
#include "Task.h"
#include "Command.h"
#include "UserInterface.h"
using namespace std;

class Command_Edit : public Command {
private:
	Task* _task;
	int _index;
	string _newName;
	int _newDate1;
	int _newDate2;
	int _newTime1;
	int _newTime2;
	string _newLocation;

	string _oldName;
	int _oldDate1;
	int _oldDate2;
	int _oldTime1;
	int _oldTime2;
	string _oldLocation;

	list<Task*>::iterator indexToListIter();
public:
	Command_Edit(list<Task*>* taskList, UserInterface* UI, int index, Task* task);
	void execute();
	void undo();
};