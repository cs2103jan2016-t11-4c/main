#include "Command_Add.h"

Command_Add::Command_Add(list<Task*>* taskList, Task* task)
:Command(taskList) {
	_task = task;
}

int Command_Add::execute() {
	_taskList->push_back(_task);
	return 1;		
}

int Command_Add::undo() {
	for(list<Task*>::iterator iter = _taskList->begin(); iter != _taskList->end(); iter++) {
		if(*iter == _task) {
			_taskList->erase(iter);
			return 1;
		}
	}
	return 0;
}