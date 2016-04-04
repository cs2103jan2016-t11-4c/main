//@@author A0125290M
#include "Command_Search.h"

Command_Search::Command_Search(string searchTerm)
:Command() {
	_searchTerm = searchTerm;
}

bool Command_Search::execute() {
	_memory->ramSearch(_searchTerm);

	return true;
}

bool Command_Search::undo() {
	_memory->ramUnsearch();
	return true;
}

string Command_Search::getSearchTerm() {
	return _searchTerm;
}

CommandType Command_Search::getCommandType() {
	return SEARCH;
}

string Command_Search::getStringForm() {
	string s = "Search term: " + _searchTerm;
	return s;
}