#include "Command_SaveDirectory.h"

Command_SaveDirectory::Command_SaveDirectory(Memory* memory, string newSaveDirectory)
:Command(memory) {
	_oldSaveDirectory = _memory->getSaveDirectory();
	_newSaveDirectory = newSaveDirectory;
}

bool Command_SaveDirectory::execute() {
	return _memory->changeSaveDirectory(_newSaveDirectory);
}

bool Command_SaveDirectory::undo() {
	return _memory->changeSaveDirectory(_oldSaveDirectory);
}

string Command_SaveDirectory::getSaveDirectory() {
	return _newSaveDirectory;
}

COMMAND_TYPE Command_SaveDirectory::getCommandType() {
	return SAVEDIRECTORY;
}