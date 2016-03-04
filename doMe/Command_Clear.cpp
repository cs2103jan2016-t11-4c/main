#include "Command_Clear.h"

Command_Clear::Command_Clear(list<Task*>* taskList, UserInterface* UI)
:Command(taskList, UI) {
	_oldTaskList = *taskList;
}

void Command_Clear::execute() {
	_taskList->clear();
	_UI->printNotificationClear();
}

void Command_Clear::undo(){
	*_taskList = _oldTaskList;
}