#include "Command_Add.h"

Command_Add::Command_Add(RAM* ram, Task* task)
:Command(ram) {
	_task = task;
}

bool Command_Add::execute() {
	if(_task == NULL) {
		return false;
	}

	_ram->add(_task);

	return true;
}

bool Command_Add::undo() {
	if(_ram->del(_task) == true) {
		return true;
	}
	return false;
}

Task* Command_Add::getTask() {
	return _task;
}

//COMMAND_TYPE Command_Add::getCommandType() {
//	return ADD;
//}