//@@author A0125290M
#include "Command_Undo.h"

Command_Undo::Command_Undo()
:Command(NULL) {
}

COMMAND_TYPE Command_Undo::getCommandType() {
	return UNDO;
}