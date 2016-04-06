//@@author A0125290M
#include "Command_Help.h"

Command_Help::Command_Help()
:Command() {
}

CommandType Command_Help::getCommandType() {
	return HELP;
}

string Command_Help::getStringForm() {
	return "Help";
}