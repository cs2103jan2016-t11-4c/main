//@@author A0125290M
#include "Command_Exit.h"

Command_Exit::Command_Exit()
	:Command() {
}

bool Command_Exit::execute() {
	if(_memory->ramGetSearchState() == true) {
		_searchTerm = _memory->ramUnsearch();
		_commandType = ENDSEARCH;
	}else {
		_commandType = EXIT;
	}

	Exception_InvalidCommand e(this);
	throw e;
}

bool Command_Exit::undo() {
	return _memory->ramSearch(_searchTerm);
}

CommandType Command_Exit::getCommandType() {
	return _commandType;
}

string Command_Exit::getStringForm() {
	return "Exit";
}