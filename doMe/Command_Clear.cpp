#include "Command_Clear.h"

Command_Clear::Command_Clear(RAM* ram)
:Command(ram) {
}

bool Command_Clear::execute() {
	_oldTaskList = _ram->clear();
	return true;
}

bool Command_Clear::undo(){
	_ram->insert(_oldTaskList);
	return true;
}

//COMMAND_TYPE Command_Clear::getCommandType() {
//	return CLEAR;
//}