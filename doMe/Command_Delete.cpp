#include "Command_Delete.h"

Command_Delete::Command_Delete(list<Task*>* taskList, int index)
:Command(taskList) {
	_index = index;
}

int Command_Delete::execute() {
	if(outOfRange()) {
		return 0;
	}

	list<Task*>::iterator deleteIter = indexToListIter();
	_task = *deleteIter;

	_taskList->erase(deleteIter);
	return 1;					
}

int Command_Delete::undo() {
	_taskList->push_back(_task);
	return 1;
}

Task* Command_Delete::getTask() {
	return _task;
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