#include "Command_Search.h"

Command_Search::Command_Search(RAM* ram, string searchTerm)
:Command(ram) {
	_searchTerm = searchTerm;
}

bool Command_Search::execute() {
	return _ram->removeTasksFromTaskList(_searchTerm);
	return true;
}

bool Command_Search::undo() {
	_ram->returnTasksToTaskList();
	return true;
}

//COMMAND_TYPE Command_Search::getCommandType() {
//	return SEARCH;
//}