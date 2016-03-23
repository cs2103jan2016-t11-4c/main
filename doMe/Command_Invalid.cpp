//@@author A0125290M
#include "Command_Invalid.h"

Command_Invalid::Command_Invalid()
:Command() {
}

bool Command_Invalid::execute() {
	return false;
}

COMMAND_TYPE Command_Invalid::getCommandType() {
	return INVALID;
}

string Command_Invalid::getStringForm() {
	return "invalid";
}