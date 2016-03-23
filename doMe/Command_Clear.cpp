//@@author A0125290M
#include "Command_Clear.h"

Command_Clear::Command_Clear(vector<int>* deleteList)
:Command() {
	_deleteList = *deleteList;
}

bool Command_Clear::execute() {
	if(outOfRange()) {
		
		return false;
	}

	if(_deleteList.empty()) {
		_oldTaskList = _memory->ramClear();
	}else {
		for(int i = 0; i < _deleteList.size(); i++) {
			_oldTaskList.push_back(_memory->ramDel(_deleteList[i]));
		}
	}

	return true;
}

bool Command_Clear::undo() {
	_memory->ramInsert(_oldTaskList);
	return true;
}

COMMAND_TYPE Command_Clear::getCommandType() {
	return CLEAR;
}

bool Command_Clear::outOfRange() {
	int biggestInteger = 0;
	int smallestInteger = 1;

	for(int i = 0; i < _deleteList.size(); i++) {
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

string Command_Clear::getStringForm() {
	return "clear";
}