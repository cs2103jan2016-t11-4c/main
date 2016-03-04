#include "Command_Delete.h"

Command_Delete::Command_Delete(list<Task*>* taskList, UserInterface* UI, int index)
:Command(taskList, UI) {
	_index = index;
}

void Command_Delete::execute() {
	if(outOfRange()) {
		_UI->printNotificationInvalidDeletion();
		return;
	}
	list<Task*>::iterator deleteIter = indexToListIter();
	_task = *deleteIter;

	_taskList->erase(deleteIter);					
}

void Command_Delete::undo() {
	_taskList->push_back(_task);
}

bool Command_Delete::outOfRange() {
	if(_index > _taskList->size() || _index < 1) {
		return true;
	}
	return false;
}

list<Task*>::iterator Command_Delete::indexToListIter() {
	list<Task*>::iterator iter = _taskList->begin();

	for(int i = 1; i < _index; i++) {
		iter++;
	}
	return iter;	
}