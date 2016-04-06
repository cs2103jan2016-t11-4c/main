//@@author A0125290M
#include "Command_Clear.h"

Command_Clear::Command_Clear(vector<int>* deleteList)
:Command() {
	_deleteList = *deleteList;
	_commandType = DEL;
}

bool Command_Clear::execute() {
	if(outOfRange()) {
		Exception_InvalidCommand e(this);
		throw e;
	}

	if(_deleteList.empty()) {
		clearAllTasks();
		_commandType = CLEAR;
	}else {
		clearSelectedTasks();
		_commandType = DEL;
	}

	return true;
}

bool Command_Clear::undo() {
	_memory->ramInsert(_oldTaskList);
	return true;
}

vector<int>* Command_Clear::getDeleteList() {
	return &_deleteList;
}

CommandType Command_Clear::getCommandType() {
	return _commandType;
}

string Command_Clear::getStringForm() {
	string s = "Clear index: ";
	for(unsigned int i = 0; i < _deleteList.size(); i++) {
		s += to_string(_deleteList[i]);
		s += ", ";
	}
	return s;
}

bool Command_Clear::outOfRange() {
	int biggestInteger = 0;
	int smallestInteger = 1;

	for(unsigned int i = 0; i < _deleteList.size(); i++) {
		if(_deleteList[i] > biggestInteger) {
			biggestInteger = _deleteList[i];
		}
		if(_deleteList[i] < smallestInteger) {
			return true;
		}
	}

	if(biggestInteger > _memory->ramGetSize()) {
		return true;
	}

	return false;
}

void Command_Clear::clearAllTasks() {
	_oldTaskList = _memory->ramClear();
}

void Command_Clear::clearSelectedTasks() {
	for(int i = _deleteList.size() - 1; i >= 0; i--) {			//delete from the back of tasklist
		_oldTaskList.push_back(_memory->ramDel(_deleteList[i]));
	}
}