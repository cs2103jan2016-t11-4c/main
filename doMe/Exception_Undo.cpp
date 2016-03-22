//@@author A0125290M
#include "Exception_Undo.h"

Exception_Undo::Exception_Undo(Command* command) {
	_command = command;
}

Command* Exception_Undo::getCommand() {
	return _command;
}