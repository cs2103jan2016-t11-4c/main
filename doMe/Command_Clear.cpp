//@@author A0125290M
#include "Command_Clear.h"

Command_Clear::Command_Clear(vector<int>& deleteList)
:Command() {
	_deleteList = deleteList;
}

bool Command_Clear::execute() {
	if(_deleteList.empty()) {
		_oldTaskList = _memory->ramClear();
	}

	for(int i = 0; i < _deleteList.size(); i++) {
		_oldTaskList.push_back(_memory->ramDel(_deleteList[i]));
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