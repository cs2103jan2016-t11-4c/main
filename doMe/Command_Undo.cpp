//@@author A0125290M
#include "Command_Undo.h"

Command_Undo::Command_Undo()
:Command() {
}

bool Command_Undo::execute() {
	return true;
}

bool Command_Undo::undo() {
	return true;
}

COMMAND_TYPE Command_Undo::getCommandType() {
	return UNDO;
}

string Command_Undo::getStringForm() {
	return "Undo";
}