#include "Command_Clear.h"

Command_Clear::Command_Clear(RAM* ram)
:Command(ram) {
}

bool Command_Clear::execute() {
	_oldTaskList = _ram->clearTaskList();
	return true;
}

bool Command_Clear::undo(){
	_ram->insertTaskList(_oldTaskList);
	return true;
}

//COMMAND_TYPE Command_Clear::getCommandType() {
//	return CLEAR;
//}