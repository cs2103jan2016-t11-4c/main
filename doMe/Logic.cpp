#include "Logic.h"

Logic::Logic(Memory* memory) {
	_memory = memory;
	_commandHistoryList = new stack<Command*>;
}

Command* Logic::executeCommand(string commandText, int& commandOutcome) {
	if(commandText.empty()) {
		Command_Invalid* commandInvalid = new Command_Invalid();
		return commandInvalid;
	}

	Parser* parser = new Parser(commandText);
	parser->parse();
	Command* command = parser->getCommand();
	delete parser;

	COMMAND_TYPE commandType = command->getCommandType();

	if(commandType == EXIT) {
		commandOutcome = 1;
		return command;
	}

	if(commandType == UNDO ) {
		commandOutcome = -1;
		return undo();
	}

	command->execute();
	_commandHistoryList->push(command);

	return command;
}

Command* Logic::undo() {
	if(_commandHistoryList->empty()) {
		Command_Undo* commandUndo = new Command_Undo();
		return commandUndo;
	}

	_commandHistoryList->top()->undo();
	Command* command = _commandHistoryList->top();
	delete _commandHistoryList->top();
	_commandHistoryList->pop();

	return command;
}