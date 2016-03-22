#include "Exception_InvalidCommand.h"

Exception_InvalidCommand::Exception_InvalidCommand(COMMAND_TYPE commandType) {
	_commandType = commandType;
}

COMMAND_TYPE Exception_InvalidCommand::getCommandType() {
	return _commandType;
}

Command* Exception_InvalidCommand::getCommand() {
    //tem still thinking @PCH
    return &Command();
}