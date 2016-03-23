//@@author A0125290M
#include "Logic.h"
Logic* Logic::_instance = NULL;

Logic::Logic() {
	_parser = Parser::getInstance();
	_memory = Memory::getInstance();
	_commandHistoryList = new stack<Command*>;
}

Logic::~Logic() {
	delete _commandHistoryList;
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

	Command* command = _parser->parse(commandText);
	assert(command != NULL);

	if(command->getCommandType() == UNDO) {
//		Exception_Undo e(undo());
//		throw e;
		undo();
		return command;
	}
		
	if(command->execute() == false) {
		Exception_InvalidCommand e(command);
		throw e;
	}

	_commandHistoryList->push(command);

	return command;
}

Command* Logic::undo() {
	if(_commandHistoryList->empty()) {
		Exception_InvalidCommand e(new Command_Undo());
		throw e;
	}

	Command* command = _commandHistoryList->top();
	command->undo();
	_commandHistoryList->pop();

	return command;
}