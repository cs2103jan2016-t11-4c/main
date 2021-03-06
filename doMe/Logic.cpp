//@@author A0125290M
#include "Logic.h"

const string Logic::LOG_MESSAGE_PARSER = "Parser parses it to be ";

Command* Logic::executeCommand(string commandText) {
	throwExceptionIfEmpty(commandText);

	Command* command = _parser->parse(commandText);
	assert(command != NULL);

	LOG(__FILE__, LOG_MESSAGE_PARSER + command->getCommandTypeStr());

	if(isUndoOrRedo(command)) {
		executeUndoRedo(command);
	}else {
		executeNormal(command);
	}

	return command;
}

void Logic::executeUndoRedo(Command* command) {
	switch(command->getCommandType()) {
		case UNDO:
			undo(command);
			break;
		case REDO:
			redo(command);
			break;
	}
}

void Logic::executeNormal(Command* command) {
	if(command->execute() == true) {		//Objects that return true are pushed onto the _commandUndoStack
		_commandUndoStack.push(command);
		clearCommandRedoStack();
	}
}

bool Logic::isUndoOrRedo(Command* command) {
	if(command->getCommandType() == UNDO || command->getCommandType() == REDO) {
		return true;
	}
	return false;
}

void Logic::undo(Command* command) {
	if(_commandUndoStack.empty()) {
		Exception_InvalidCommand e(new Command_Undo());
		throw e;
	}

	Command* undoneCommand = _commandUndoStack.top();
	undoneCommand->undo();

	command->setUndoneCommand(undoneCommand);
	_commandUndoStack.pop();

	_commandRedoStack.push(undoneCommand);

}

void Logic::redo(Command* command) {
	if(_commandRedoStack.empty()) {
		Exception_InvalidCommand e(new Command_Redo());
		throw e;
	}
	Command* redoneCommand = _commandRedoStack.top();
	redoneCommand->execute();

	command->setRedoneCommand(redoneCommand);

	_commandRedoStack.pop();
	_commandUndoStack.push(redoneCommand);
}

void Logic::clearCommandRedoStack() {
	while(!_commandRedoStack.empty()) {
		_commandRedoStack.pop();
	}
}

void Logic::throwExceptionIfEmpty(string commandText) {
	if(isBlank(commandText)) {
		Exception_InvalidCommand e(new Command_Invalid());
		throw e;
	}
}

bool Logic::isBlank(string commandText) {
	if(commandText.empty()) {
		return true;
	}

	for(unsigned int i = 0; i < commandText.size(); i++) {
		if(commandText[i] != ' ') {
			return false;
		}
	}

	return true;
}

/**********************************************************************/

Logic* Logic::_instance = NULL;

Logic::Logic() {
	_parser = Parser::getInstance();
}

Logic* Logic::getInstance() {
	if (_instance == NULL) {
		_instance = new Logic;
	}
	return _instance;
}