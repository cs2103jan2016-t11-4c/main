#include "Command_Exit.h"

Command_Exit::Command_Exit()
:Command(NULL) {
}

COMMAND_TYPE Command_Exit::getCommandType() {
	return EXIT;
}