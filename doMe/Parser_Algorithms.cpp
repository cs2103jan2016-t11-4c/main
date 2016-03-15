#include "Parser_Algorithms.h"


Parser_Algorithms::Parser_Algorithms(CommandTokens* tokens) :
	_tokens(tokens)
{
	packInvalidCommand();
}

Parser_Algorithms::~Parser_Algorithms(void)
{
}

CommandPackage Parser_Algorithms::parse() {
	
	branchToNodes(START_INDEX);
	return _commandPackage;
}

void Parser_Algorithms::branchToNodes(int index) {
	assert(!_tokens->isOutOfBounds(index));
	if(_tokens->hasMeaning("DISPLAY", index)) {
		nodeOneOfDisplayCommand(index+1);
	} else if(_tokens->hasMeaning("EDIT", index)) {
		nodeOneOfChangeDirectoryCommand(index+1);
	} else if(_tokens->hasMeaning("DEL", index)) {
		nodeOneOfDeleteCommand(index+1);
	} else if(_tokens->hasMeaning("UNDO", index)) {
		nodeOneOfUndoCommand(index+1);
	} else if(_tokens->hasMeaning("EXIT", index)) {
		nodeOneOfExitCommand(index+1);
	} else if(_tokens->hasMeaning("SEARCH", index)) {
		nodeOneOfSearchCommand(index+1);
	} else if(_tokens->hasMeaning("CLEAR", index)) {
		nodeOneOfClearCommand(index+1);
	} else if(_tokens->hasMeaning("CHANGEDIRECTORY", index)) {
		nodeTwoOfChangeDirectoryCommand(index+1);
	} else if(_tokens->hasMeaning("CHANGEVIEWTYPE", index)) {
		nodeTwoOfChangeViewTypeCommand(index+1);
	} else {
		nodeOneOfAddCommand(index);
	}
	return;
}
//done
void Parser_Algorithms::nodeOneOfDisplayCommand(int index) {
	if(_tokens->noMoreTokens(index)) {
		packDisplayCommand();
	} else {
		nodeTwoOfChangeViewTypeCommand(index);
	}
	return;
}
//done
void Parser_Algorithms::packDisplayCommand() {
	_commandPackage = CommandPackage(DISPLAY);
	return;
}
//done
void Parser_Algorithms::nodeOneOfChangeDirectoryCommand(int index) {
	if(_tokens->noMoreTokens(index)) {
		packInvalidCommand();
	} else if(_tokens->hasMeaning("DIRECTORY", index)) {
		nodeTwoOfChangeDirectoryCommand(index+1);
	} else {
		nodeOneOfChangeViewTypeCommand(index);
	}
	return;
}
//done
void Parser_Algorithms::nodeTwoOfChangeDirectoryCommand(int index) {
	if(_tokens->noMoreTokens(index)) {
		packInvalidCommand();
	} else {
		_description = _tokens->getOriginalToken(index);
		nodeThreeOfChangeDirectoryCommand(index+1);
	}
	return;
}
//done
void Parser_Algorithms::nodeThreeOfChangeDirectoryCommand(int index) {
	if(_tokens->noMoreTokens(index)) {
		packChangeDirectoryCommand();
	} else {
		nodeOneOfAddCommand(START_INDEX);
	}
	return;
}
//done
void Parser_Algorithms::packChangeDirectoryCommand() {
	_commandPackage = CommandPackage(SAVEDIRECTORY, Task(), NO_INDEX, _description);
	return;
}
//i think is done
void Parser_Algorithms::nodeOneOfChangeViewTypeCommand(int index) {
	if(_tokens->noMoreTokens(index)) {
		packInvalidCommand();
	} else if(_tokens->hasMeaning("DISPLAY", index)) {
		nodeTwoOfChangeViewTypeCommand(index+1);
	} else {
		nodeOneOfEditCommand(index);
	}
	return;
}
//done
void Parser_Algorithms::nodeTwoOfChangeViewTypeCommand(int index) {
	if(_tokens->noMoreTokens(index)) {
		packInvalidCommand();
	} else if(_tokens->isInteger(index)) {
		_index = stoi(_tokens->getToken(index));
		nodeThreeOfChangeViewTypeCommand(index+1);
	} else {
		nodeOneOfAddCommand(START_INDEX);
	}
	return;
}
//dome
void Parser_Algorithms::nodeThreeOfChangeViewTypeCommand(int index) {
	if(_tokens->noMoreTokens(index)) {
		packChangeViewTypeCommand();
	} else {
		nodeOneOfAddCommand(START_INDEX);
	}
	return;
}
//done
void Parser_Algorithms::packChangeViewTypeCommand() {
	_commandPackage = CommandPackage(VIEWTYPE, Task(), _index);
	return;
}
//done
void Parser_Algorithms::nodeOneOfDeleteCommand(int index) {
	if(_tokens->noMoreTokens(index)) {
		packInvalidCommand();
	} else if(_tokens->isInteger(index)) {
		_index = stoi(_tokens->getToken(index));
		nodeTwoOfDeleteCommand(index+1);
	} else {
		nodeOneOfAddCommand(START_INDEX);
	}
	return;
}
//done
void Parser_Algorithms::nodeTwoOfDeleteCommand(int index) {
	if(_tokens->noMoreTokens(index)) {
		packDeleteCommand();
	} else {
		packInvalidCommand();
	}
	return;
}
//done
void Parser_Algorithms::packDeleteCommand() {
	_commandPackage = CommandPackage(DEL, Task(), _index);
	return;
}
//done
void Parser_Algorithms::nodeOneOfUndoCommand(int index) {
	if(_tokens->noMoreTokens(index)) {
		packUndoCommand();
	} else {
		nodeOneOfAddCommand(START_INDEX);
	}
	return;
}
//done
void Parser_Algorithms::packUndoCommand() {
	_commandPackage = CommandPackage(UNDO);
	return;
}
//done
void Parser_Algorithms::nodeOneOfExitCommand(int index) {
	if(_tokens->noMoreTokens(index)) {
		packExitCommand();
	} else {
		nodeOneOfAddCommand(START_INDEX);
	}
	return;
}
//done
void Parser_Algorithms::packExitCommand() {
	_commandPackage = CommandPackage(EXIT);
	return;
}
//done
void Parser_Algorithms::nodeOneOfClearCommand(int index) {
	if(_tokens->noMoreTokens(index)) {
		packClearCommand();
	} else {
		nodeOneOfDeleteCommand(index);
	}
	return;
}
//done
void Parser_Algorithms::packClearCommand() {
	_commandPackage = CommandPackage(CLEAR);
	return;
}
//done
void Parser_Algorithms::nodeOneOfSearchCommand(int index) {
	if(_tokens->noMoreTokens(index)) {
		packInvalidCommand();
	} else {
		_description = _tokens->getOriginalToken(index);
		nodeTwoOfSearchCommand(index+1);
	}
	return;
}
//done
void Parser_Algorithms::nodeTwoOfSearchCommand(int index) {
	if(_tokens->noMoreTokens(index)) {
		packSearchCommand();
	} else {
		nodeOneOfAddCommand(START_INDEX);
	}
	return;
}
//done
void Parser_Algorithms::packSearchCommand() {
	_commandPackage = CommandPackage(SEARCH, Task(), NO_INDEX, _description);
	return;
}
//done
void Parser_Algorithms::packInvalidCommand() {
	_commandPackage = CommandPackage(INVALID);
	return;
}

void Parser_Algorithms::nodeOneOfAddCommand(int index) {
	Parser_Tasks taskParser(_tokens);
	_task = taskParser.getTask(index);
	packAddCommand();
	return;
}

void Parser_Algorithms::packAddCommand() {
	_commandPackage = CommandPackage(ADD, _task);
	return;
}

void Parser_Algorithms::nodeOneOfEditCommand(int index) {
	if(_tokens->noMoreTokens(index)) {
		packInvalidCommand();
	} else if(_tokens->isInteger(index)) {
		_index = stoi(_tokens->getToken(index));
		nodeTwoOfEditCommand(index+1);
	} else {
		_index = LAST_INDEX;
		nodeTwoOfEditCommand(index);
	}
	return;
}

void Parser_Algorithms::nodeTwoOfEditCommand(int index) {
	if(_tokens->noMoreTokens(index)) {
		packInvalidCommand();
	} else {
		Parser_Tasks taskParser(_tokens);
		_task = taskParser.getTask(index);
		packEditCommand();
	}
	return;
}

void Parser_Algorithms::packEditCommand() {
	_commandPackage = CommandPackage(EDIT, _task, _index);
	return;
}