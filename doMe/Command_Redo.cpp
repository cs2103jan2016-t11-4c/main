//@@author A0125290M
#include "Command_Redo.h"

Command_Redo::Command_Redo()
:Command() {
}

bool Command_Redo::execute() {
	return true;
}

bool Command_Redo::undo() {
	return true;
}

void Command_Redo::setRedoneCommand(Command* command) {
	_redoneCommand = command;
}

Command* Command_Redo::getRedoneCommand() {
	return _redoneCommand;
}

CommandType Command_Redo::getCommandType() {
	return REDO;
}

string Command_Redo::getStringForm() {
	return "Redo";
}