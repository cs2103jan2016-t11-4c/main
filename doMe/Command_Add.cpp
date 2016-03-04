#include "Command_Add.h"

Command_Add::Command_Add(list<Task*>* taskList, UserInterface* UI, Task* task)
:Command(taskList, UI) {
	_task = task;
}

void Command_Add::execute() {
	_taskList->push_back(_task);
	_UI->printNotificationAdd(_task);		
}

void Command_Add::undo() {
	for(list<Task*>::iterator iter = _taskList->begin(); iter != _taskList->end(); iter++) {
		if(*iter == _task) {
			_taskList->erase(iter);
			return;
		}
	}
}