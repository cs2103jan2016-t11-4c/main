//@@author A0125290M
#include "Command_Add.h"

Command_Add::Command_Add(Task* task)
:Command(){
	_task = task;
}

bool Command_Add::execute() {

	if(_task == NULL) {
		return false;
	}

	_memory->ramAdd(_task);

	return true;
}

bool Command_Add::undo() {
	_memory->ramDel(_task);
	return true;
}

Task* Command_Add::getTask() {
	return _task;
}

COMMAND_TYPE Command_Add::getCommandType() {
	return ADD;
}