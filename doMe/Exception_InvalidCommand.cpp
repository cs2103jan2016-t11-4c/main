//@@author A0125290M
#include "Exception_InvalidCommand.h"

Exception_InvalidCommand::Exception_InvalidCommand(Command* command) {
	_command = command;
}

Command* Exception_InvalidCommand::getCommand() {
	return _command;
}