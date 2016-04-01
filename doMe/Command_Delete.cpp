//@@author A0125290M
#include "Command_Delete.h"

Command_Delete::Command_Delete(int index)
:Command() {
	_index = index;
}

bool Command_Delete::execute() {
	if(outOfRange()) {
		return false;
	}

	_task = _memory->ramDel(_index);

	return true;
}

bool Command_Delete::undo() {
	_memory->ramAdd(_task);
	return true;
}

Task* Command_Delete::getTask() {
	return _task;
}

CommandType Command_Delete::getCommandType() {
	return DEL;
}

bool Command_Delete::outOfRange() {
	if(_index > _memory->ramGetSize() || _index < 1) {
		return true;
	}
	return false;
}

string Command_Delete::getStringForm() {
	string s = "Delete index: " + to_string(_index);
	return s;
}