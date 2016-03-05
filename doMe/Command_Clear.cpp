#include "Command_Clear.h"

Command_Clear::Command_Clear(list<Task*>* taskList)
:Command(taskList) {
	_oldTaskList = *taskList;
}

int Command_Clear::execute() {
	_taskList->clear();
	return 1;
}

int Command_Clear::undo(){
	*_taskList = _oldTaskList;
	return 1;
}