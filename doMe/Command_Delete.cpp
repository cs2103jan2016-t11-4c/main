#include "Command_Delete.h"

Command_Delete::Command_Delete(RAM* ram, int index)
:Command(ram) {
	_index = index;
}

bool Command_Delete::execute() {
	if(outOfRange()) {
		return false;
	}

	_task = _ram->del(_index);

	return true;
}

bool Command_Delete::undo() {
	_ram->add(_task);
	return true;
}

Task* Command_Delete::getTask() {
	return _task;
}

bool Command_Delete::outOfRange() {
	if(_index > _ram->getSize() || _index < 1) {
		return true;
	}
	return false;
}

//COMMAND_TYPE Command_Delete::getCommandType() {
//	return DELETE;
//}