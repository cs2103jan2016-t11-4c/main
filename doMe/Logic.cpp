//@@author A0125290M
#include "Logic.h"
Logic* Logic::_instance = NULL;

Logic::Logic() {
	_parser = Parser::getInstance();
	_memory = Memory::getInstance();
}

Logic::~Logic() {
}

Logic* Logic::getInstance() {
	if (_instance == NULL) {
		_instance = new Logic;
	}
	return _instance;
}

Command* Logic::executeCommand(string commandText) {
	throwExceptionIfEmpty(commandText);

	Command* command = _parser->parse(commandText);
	assert(command != NULL);

	LOG(__FILE__, "Parser parses it to be " + command->getCommandTypeStr());

	if(command->getCommandType() == UNDO || command->getCommandType() == REDO) {
		executeUndoRedo(command);
		return command;
	}

	command->execute();
	_commandUndoStack.push(command);
	clearCommandRedoStack();

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

void Logic::undo(Command* command) {
	if(_commandUndoStack.empty()) {
		Exception_InvalidCommand e(new Command_Undo());
		throw e;
	}

	Command* undoneCommand = _commandUndoStack.top();
	undoneCommand->undo();

	command->setUndoneCommand(undoneCommand);
	_commandUndoStack.pop();

	_commandRedoStack.push(command);

}

void Logic::redo(Command* command) {
	if(_commandRedoStack.empty()) {
//		Exception_InvalidCommand e(new Command_Redo());
//		throw e;
	}
	Command* redoneCommand = _commandRedoStack.top();
	redoneCommand->execute();

	command->setRedoneCommand(redoneCommand);

	_commandRedoStack.pop();
	_commandUndoStack.push(command);
}

void Logic::clearCommandRedoStack() {
	while(!_commandRedoStack.empty()) {
		_commandRedoStack.pop();
	}
}

void Logic::throwExceptionIfEmpty(string commandText) {
	if(commandText.empty()) {
		Exception_InvalidCommand e(new Command_Invalid());
		throw e;
	}
}