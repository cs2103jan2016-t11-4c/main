#include "Command_Invalid.h"

Command_Invalid::Command_Invalid()
:Command(NULL) {
}

COMMAND_TYPE Command_Invalid::getCommandType() {
	return INVALID;
}