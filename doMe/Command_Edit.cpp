//@@author A0125290M
#include "Command_Edit.h"

const int Command_Edit::DATE_NO_CHANGE = -2;
const int Command_Edit::TIME_NO_CHANGE = -2;
const string Command_Edit::LOCATION_NO_CHANGE = " ";

Command_Edit::Command_Edit(int index, Task* task)
:Command() {
	_index = index;
	_newName = task->getName();
	_newDate1 = task->getDate1();
	_newDate2 = task->getDate2();
	_newTime1 = task->getTime1();
	_newTime2 = task->getTime2();
	_newLocation = task->getLocation();
	_newDoneStatus = task->getDoneStatus();
}

bool Command_Edit::execute() {
	if(outOfRange()) {
		Exception_InvalidCommand e(this);
		throw e;
	}

	_task = _memory->ramGetTask(_index);

	_oldName = _task->getName();
	_oldDate1 = _task->getDate1();
	_oldDate2 = _task->getDate2();
	_oldTime1 = _task->getTime1();
	_oldTime2 = _task->getTime2();
	_oldLocation = _task->getLocation();
	_oldDoneStatus = _task->getDoneStatus();

	if(!_newName.empty()) {
		_task->setName(_newName);
	}
	if(_newDate1 != DATE_NO_CHANGE) {
		_task->setDate1(_newDate1);
	}
	if(_newDate2 != DATE_NO_CHANGE) {
		_task->setDate2(_newDate2);
	}
	if(_newTime1 != TIME_NO_CHANGE) {
		_task->setTime1(_newTime1);
	}
	if(_newTime2 != TIME_NO_CHANGE) {
		_task->setTime2(_newTime2);
	}
	if(_newLocation != LOCATION_NO_CHANGE) {
		_task->setLocation(_newLocation);
	}
	if(_newDoneStatus != -1) {
		_task->setDoneStatus(_newDoneStatus);
	}

	_memory->ramSort();
	_memory->saveRam();
	return true;
}

bool Command_Edit::undo() {
	_task->setName(_oldName);
	_task->setTime1(_oldTime1);
	_task->setTime2(_oldTime2);
	_task->setDate1(_oldDate1);
	_task->setDate2(_oldDate2);
	_task->setLocation(_oldLocation);
	_task->setDoneStatus(_oldDoneStatus);

	_memory->ramSort();
	_memory->saveRam();
	return true;
}

Task* Command_Edit::getTask() {
	return _task;
}

CommandType Command_Edit::getCommandType() {
	return EDIT;
}

string Command_Edit::getStringForm() {
	string s = "Edit index: " + to_string(_index) + " task- ";
	s += "name: " + _newName;
	s += ", location: " + _newLocation;
	s += ", date1: " + to_string(_newDate1);
	s += ", date2: " + to_string(_newDate2);
	s += ", time1: " + to_string(_newTime1);
	s += ", time2: " + to_string(_newTime2);
	s += ", doneStatus: " + to_string(_newDoneStatus);
	return s;
}

bool Command_Edit::outOfRange() {
	if(_index > _memory->ramGetSize() || _index < 0) {
		return true;
	}
	return false;
}