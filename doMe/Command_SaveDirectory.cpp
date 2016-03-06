#include "Command_SaveDirectory.h"

Command_SaveDirectory::Command_SaveDirectory(Settings* settings, string newSaveDirectory)
:Command(NULL) {
	_settings = settings;
	_oldSaveDirectory = _settings->getSaveDirectory();
	_newSaveDirectory = newSaveDirectory;
}

int Command_SaveDirectory::execute() {
	if(isNotValidDirectory()) {
		return 0;
	}

	_settings->changeSaveDirectory(_newSaveDirectory);
	return 1;
}

int Command_SaveDirectory::undo(){
	_settings->changeSaveDirectory(_oldSaveDirectory);
	return 1;	
}

string Command_SaveDirectory::getDescription() {
	return _newSaveDirectory;
}

bool Command_SaveDirectory::isNotValidDirectory() {
	struct stat info;

	if(stat(_newSaveDirectory.c_str(), &info) != 0) {
		return true;
	}else if(info.st_mode & S_IFDIR) {
		return false;
	}
	return true;
}