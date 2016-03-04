#include "Command_Edit.h"

Command_Edit::Command_Edit(list<Task*>* taskList, UserInterface* UI, int index, Task* oldTask)
:Command(taskList, UI) {
	_index = index;
	_newName = oldTask->getName();
	_newDate1 = oldTask->getDate1();
	_newDate2 = oldTask->getDate2();
	_newTime1 = oldTask->getTime1();
	_newTime2 = oldTask->getTime2();
	_newLocation = oldTask->getLocation();
}

void Command_Edit::execute() {
	list<Task*>::iterator editIter = indexToListIter();

	_task = *editIter;

	if(!_newName.empty()) {
		_oldName = _task->getName();
		_task->setName(_newName);
	}
	if(_newDate1 != -1) {
		_oldDate1 = _task->getDate1();
		_task->setDate1(_newDate1);
	}
	if(_newDate2 != -1) {
		_oldDate2 = _task->getDate2();
		_task->setDate2(_newDate2);
	}
	if(_newTime1 != -1) {
		_oldTime1 = _task->getTime1();
		_task->setTime1(_newTime1);
	}
	if(_newTime2 != -1) {
		_oldTime2 = _task->getTime2();
		_task->setTime2(_newTime2);
	}
	if(!_newLocation.empty()) {
		_oldLocation = _task->getLocation();
		_task->setLocation(_newLocation);
	}
}

void Command_Edit::undo() {
	_task->setName(_oldName);
	_task->setTime1(_oldTime1);
	_task->setTime2(_oldTime2);
	_task->setDate1(_oldDate1);
	_task->setDate2(_oldDate2);
	_task->setLocation(_oldLocation);
}

list<Task*>::iterator Command_Edit::indexToListIter() {
	list<Task*>::iterator iter = _taskList->begin();

	for(int i = 1; i < _index; i++) {
		iter++;
	}
	return iter;	
}