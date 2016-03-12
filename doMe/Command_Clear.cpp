#include "Command_Clear.h"

Command_Clear::Command_Clear(Memory* memory)
:Command(memory) {
}

bool Command_Clear::execute() {
	_oldTaskList = _memory->ramClear();
	return true;
}

bool Command_Clear::undo() {
	_memory->ramInsert(_oldTaskList);
	return true;
}

COMMAND_TYPE Command_Clear::getCommandType() {
	return CLEAR;
}