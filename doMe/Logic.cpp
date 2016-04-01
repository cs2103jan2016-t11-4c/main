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
	if(commandText.empty()) {
		Exception_InvalidCommand e(new Command_Invalid());
		throw e;
	}

	LOG(__FILE__,"User enters: \" " + commandText + "\"");

	Command* command = _parser->parse(commandText);
	assert(command != NULL);

	LOG(__FILE__, "Parser parses it to be " + command->getCommandTypeStr());

	if(command->getCommandType() == UNDO) {
		command->setUndoneCommand(undo());
		return command;
	}

	if(command->getCommandType() == REDO) {
		command->setRedoneCommand(redo());
		return command;
	}

	if(command->execute() == false) {
		Exception_InvalidCommand e(command);
		throw e;
	}

	_commandUndoStack.push(command);
	clearCommandRedoStack();

	return command;
}

Command* Logic::undo() {
	if(_commandUndoStack.empty()) {
		Exception_InvalidCommand e(new Command_Undo());
		throw e;
	}

	Command* command = _commandUndoStack.top();
	command->undo();
	_commandUndoStack.pop();
	_commandRedoStack.push(command);

	return command;
}

Command* Logic::redo() {
	if(_commandRedoStack.empty()) {
//		Exception_InvalidCommand e(new Command_Redo());
//		throw e;
	}
	Command* command = _commandRedoStack.top();
	command->execute();
	_commandRedoStack.pop();
	_commandUndoStack.push(command);

	return command;
}

void Logic::clearCommandRedoStack() {
	while(!_commandRedoStack.empty()) {
		_commandRedoStack.pop();
	}
}