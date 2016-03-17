//@@author A0125290M
#include "Logic.h"

Logic::Logic() {
	_commandHistoryList = new stack<Command*>;
}

Command* Logic::executeCommand(string commandText, int& commandOutcome) {
//	if(commandText.empty()) {
//		Command_Invalid* commandInvalid = new Command_Invalid();
//		return commandInvalid;
//	}

	Parser* parser = new Parser(commandText);
	parser->parse();
	Command* command = parser->getCommand();
	assert(command != NULL);
	//delete parser;

	if(command->getCommandType() == UNDO ) {
		commandOutcome = -1;
		return undo();
	}

	if(command->execute() == true) {
		_commandHistoryList->push(command);
		commandOutcome = 1;
	}else {
		commandOutcome = 0;
	}

	return command;
}

Command* Logic::undo() {
	if(_commandHistoryList->empty()) {
		Command_Invalid* commandInvalid = new Command_Invalid();
		return commandInvalid;
	}

	_commandHistoryList->top()->undo();
	Command* command = _commandHistoryList->top();
	delete _commandHistoryList->top();
	_commandHistoryList->pop();

	return command;
}