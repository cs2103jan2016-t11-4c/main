//@@author A0122569B

#include "Parser.h"

Parser* Parser::_theOne = NULL;

Parser::Parser(void) {
	_commandPacker = CommandPacker::getInstance();
}

Parser::~Parser(void) {
}

Parser* Parser::getInstance() {
	if(_theOne == NULL) {
		_theOne = new Parser;
	}

	return _theOne;
}

Command* Parser::parse(string userInput) {
	assert(userInput.size() != 0);

	InputTokens* tokens = new InputTokens(userInput);
	Command* command = _commandPacker->packCommand(tokens);
	
	delete tokens;
	return command;
}