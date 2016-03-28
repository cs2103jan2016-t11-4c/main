//@@author A0125290M
#include "Command_SaveDirectory.h"

Command_SaveDirectory::Command_SaveDirectory(string newSaveDirectory)
:Command() {
	_oldSaveDirectory = _memory->getSaveDirectory();
	_newSaveDirectory = newSaveDirectory;
}

bool Command_SaveDirectory::execute() {
	return _memory->changeSaveDirectory(_newSaveDirectory);
}

bool Command_SaveDirectory::undo() {
	_memory->changeSaveDirectory(_oldSaveDirectory);
	return true;
}

string Command_SaveDirectory::getSaveDirectory() {
	return _newSaveDirectory;
}

COMMAND_TYPE Command_SaveDirectory::getCommandType() {
	return SAVEDIRECTORY;
}