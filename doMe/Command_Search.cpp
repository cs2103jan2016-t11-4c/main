//@@author A0125290M
#include "Command_Search.h"

Command_Search::Command_Search(string searchTerm)
:Command() {
	_searchTerm = searchTerm;
}

bool Command_Search::execute() {
	return _memory->ramSearch(_searchTerm);
}

bool Command_Search::undo() {
	_memory->ramUnsearch();
	return true;
}

string Command_Search::getSearchTerm() {
	return _searchTerm;
}

COMMAND_TYPE Command_Search::getCommandType() {
	return SEARCH;
}