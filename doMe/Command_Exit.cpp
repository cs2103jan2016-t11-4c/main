//@@author A0125290M
#include "Command_Exit.h"

Command_Exit::Command_Exit()
:Command() {
}

bool Command_Exit::execute() {
	if(_memory->ramGetSearchState() == true) {
		_searchTerm = _memory->ramUnsearch();
		_commandType = ENDSEARCH;
		return true;
	}
	_commandType = EXIT;
	return false;
}

bool Command_Exit::undo() {
	return _memory->ramSearch(_searchTerm);
}

COMMAND_TYPE Command_Exit::getCommandType() {
	return EXIT;
}

string Command_Exit::getStringForm() {
	return "exit";
}