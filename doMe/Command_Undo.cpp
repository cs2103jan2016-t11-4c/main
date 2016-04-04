//@@author A0125290M
#include "Command_Undo.h"

Command_Undo::Command_Undo()
:Command() {
}

void Command_Undo::setUndoneCommand(Command* command) {
	_undoneCommand = command;
}

Command* Command_Undo::getUndoneCommand() {
	return _undoneCommand;
}

CommandType Command_Undo::getCommandType() {
	return UNDO;
}

string Command_Undo::getStringForm() {
	return "Undo";
}