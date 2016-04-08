//@@author A0125290M
#include "Command_Edit.h"

const int Command_Edit::DATE_NO_CHANGE = -2;
const int Command_Edit::TIME_NO_CHANGE = -2;
const string Command_Edit::LOCATION_NO_CHANGE = " ";

Command_Edit::Command_Edit(vector<int>* editList, Task* task)
	:Command() {
		_editList = *editList;
		_newName = task->getName();
		_newDate1 = task->getDate1();
		_newDate2 = task->getDate2();
		_newTime1 = task->getTime1();
		_newTime2 = task->getTime2();
		_newLocation = task->getLocation();
		_newDoneStatus = task->getDoneStatus();
		if(_editList.size() == 1) {
			_commandType = EDIT;
		}else{
			_commandType = EDIT_MULTIPLE;
		}
}

bool Command_Edit::execute() {
	if(outOfRange()) {
		Exception_InvalidCommand e(this);
		throw e;
	}

	if(_editList.empty()) {
		editAllTasks();
	}else {
		editSelectedTasks();
	}
	_memory->ramSort();
	_memory->saveRam();

	return true;
}

void Command_Edit::editAllTasks() {
	for(unsigned int i = 0; i < _memory->ramGetSize(); i++) {
		_edittedTaskPtrList.push_back(_memory->ramGetTask(i));
		_oldTaskList.push_back(*_edittedTaskPtrList.back());

		if(!_newName.empty()) {
			_edittedTaskPtrList.back()->setName(_newName);
		}
		if(_newDate1 != DATE_NO_CHANGE) {
			_edittedTaskPtrList.back()->setDate1(_newDate1);
		}
		if(_newDate2 != DATE_NO_CHANGE) {
			_edittedTaskPtrList.back()->setDate2(_newDate2);
		}
		if(_newTime1 != TIME_NO_CHANGE) {
			_edittedTaskPtrList.back()->setTime1(_newTime1);
		}
		if(_newTime2 != TIME_NO_CHANGE) {
			_edittedTaskPtrList.back()->setTime2(_newTime2);
		}
		if(_newLocation != LOCATION_NO_CHANGE) {
			_edittedTaskPtrList.back()->setLocation(_newLocation);
		}
		if(_newDoneStatus != -1) {
			_edittedTaskPtrList.back()->setDoneStatus(_newDoneStatus);
		}
	}

}

void Command_Edit::editSelectedTasks() {
	for(unsigned int i = 0; i < _editList.size(); i++) {
		_edittedTaskPtrList.push_back(_memory->ramGetTask(_editList[i]));
		_oldTaskList.push_back(*_edittedTaskPtrList.back());

		if(!_newName.empty()) {
			_edittedTaskPtrList.back()->setName(_newName);
		}
		if(_newDate1 != DATE_NO_CHANGE) {
			_edittedTaskPtrList.back()->setDate1(_newDate1);
		}
		if(_newDate2 != DATE_NO_CHANGE) {
			_edittedTaskPtrList.back()->setDate2(_newDate2);
		}
		if(_newTime1 != TIME_NO_CHANGE) {
			_edittedTaskPtrList.back()->setTime1(_newTime1);
		}
		if(_newTime2 != TIME_NO_CHANGE) {
			_edittedTaskPtrList.back()->setTime2(_newTime2);
		}
		if(_newLocation != LOCATION_NO_CHANGE) {
			_edittedTaskPtrList.back()->setLocation(_newLocation);
		}
		if(_newDoneStatus != -1) {
			_edittedTaskPtrList.back()->setDoneStatus(_newDoneStatus);
		}
	}
}

bool Command_Edit::undo() {
	for(unsigned int i = 0; i < _edittedTaskPtrList.size(); i++) {
		_edittedTaskPtrList[i]->setName(_oldTaskList[i].getName());
		_edittedTaskPtrList[i]->setTime1(_oldTaskList[i].getTime1());
		_edittedTaskPtrList[i]->setTime2(_oldTaskList[i].getTime2());
		_edittedTaskPtrList[i]->setDate1(_oldTaskList[i].getDate1());
		_edittedTaskPtrList[i]->setDate2(_oldTaskList[i].getDate2());
		_edittedTaskPtrList[i]->setLocation(_oldTaskList[i].getLocation());
		_edittedTaskPtrList[i]->setDoneStatus(_oldTaskList[i].getDoneStatus());
	}
	_memory->ramSort();
	_memory->saveRam();
	return true;
}

Task* Command_Edit::getTask() {
	return _edittedTaskPtrList.front();
}

vector<int>* Command_Edit::getEditList() {
	return &_editList;
}

CommandType Command_Edit::getCommandType() {
	return _commandType;
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
	int biggestInteger = 0;
	int smallestInteger = 0;

	for(unsigned int i = 0; i < _editList.size(); i++) {
		if(_editList[i] > biggestInteger) {
			biggestInteger = _editList[i];
		}
		if(_editList[i] < smallestInteger) {
			return true;
		}
	}

	if(biggestInteger > _memory->ramGetSize()) {
		return true;
	}

	return false;
}