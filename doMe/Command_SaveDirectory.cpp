//@@author A0125290M
#include "Command_SaveDirectory.h"

Command_SaveDirectory::Command_SaveDirectory(string newSaveDirectory)
:Command() {
	_oldSaveDirectory = _memory->getSaveDirectory();
	_newSaveDirectory = newSaveDirectory;
}

bool Command_SaveDirectory::execute() {
	_errorType = _memory->changeSaveDirectory(_newSaveDirectory);

	if(_errorType == 1) {
		return true;
	}

	return false;
}

bool Command_SaveDirectory::undo() {
	return _memory->changeSaveDirectory(_oldSaveDirectory);
}

string Command_SaveDirectory::getSaveDirectory() {
	return _newSaveDirectory;
}

int Command_SaveDirectory::getErrorType() {
	return _errorType;
}

COMMAND_TYPE Command_SaveDirectory::getCommandType() {
	return SAVEDIRECTORY;
}