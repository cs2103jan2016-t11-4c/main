//@@author A0125290M
#include "Command_Edit.h"

Command_Edit::Command_Edit(int index, Task* task)
:Command() {
	_index = index;
	_newName = task->getName();
	_newDate1 = task->getDate1();
	_newDate2 = task->getDate2();
	_newTime1 = task->getTime1();
	_newTime2 = task->getTime2();
	_newLocation = task->getLocation();
//	_newDoneStatus = task->getDoneStatus();
}

bool Command_Edit::execute() {
	if(outOfRange()) {
		return false;
	}

	_task = _memory->ramGetTask(_index);

	_oldName = _task->getName();
	_oldDate1 = _task->getDate1();
	_oldDate2 = _task->getDate2();
	_oldTime1 = _task->getTime1();
	_oldTime2 = _task->getTime2();
	_oldLocation = _task->getLocation();
//	_oldDoneStatus = _task->getDoneStatus();

	if(!_newName.empty()) {
		_task->setName(_newName);
	}
	if(_newDate1 != -1) {
		_task->setDate1(_newDate1);
	}
	if(_newDate2 != -1) {
		_task->setDate2(_newDate2);
	}
	if(_newTime1 != -1) {
		_task->setTime1(_newTime1);
	}
	if(_newTime2 != -1) {
		_task->setTime2(_newTime2);
	}
	if(!_newLocation.empty()) {
		_task->setLocation(_newLocation);
	}
/*	if(!_newDoneStatus != -1) {
		_task->setDoneStatus(_newDoneStatus);
	}*/
	_memory->ramSort();
	return true;
}

bool Command_Edit::undo() {
	_task->setName(_oldName);
	_task->setTime1(_oldTime1);
	_task->setTime2(_oldTime2);
	_task->setDate1(_oldDate1);
	_task->setDate2(_oldDate2);
	_task->setLocation(_oldLocation);
	_memory->ramSort();
	return true;
}

Task* Command_Edit::getTask() {
	return _task;
}

COMMAND_TYPE Command_Edit::getCommandType() {
	return EDIT;
}

bool Command_Edit::outOfRange() {
	if(_index > _memory->ramGetSize() || _index < 0) {
		return true;
	}
	return false;
}

string Command_Edit::getStringForm() {
	string s = "Edit index: " + to_string(_index) + " task- ";
	s += "name: " + _newName;
	s += ", location: " + _newLocation;
	s += ", date1: " + to_string(_newDate1);
	s += ", date2: " + to_string(_newDate2);
	s += ", time1: " + to_string(_newTime1);
	s += ", time1: " + to_string(_newTime2);
	return s;
}