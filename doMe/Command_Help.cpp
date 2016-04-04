//@@author A0125290M
#include "Command_Help.h"

Command_Help::Command_Help()
:Command() {
}

bool Command_Help::execute() {
	return false;
}

CommandType Command_Help::getCommandType() {
	return HELP;
}

string Command_Help::getStringForm() {
	return "Help";
}