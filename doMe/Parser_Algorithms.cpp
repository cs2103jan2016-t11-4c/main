#include "Parser_Algorithms.h"

Parser_Algorithms::Parser_Algorithms(CommandTokens* tokens) :
	_tokens(tokens)
{
	initializeAttributes();
}

Parser_Algorithms::~Parser_Algorithms(void)
{
}

void Parser_Algorithms::initializeAttributes() {
	_singleIndex = NO_VALUE;
	_description = NO_STRING;
	_task = NO_TASK;

	return;
}

Command* Parser_Algorithms::parse() {
	
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


void Parser_Algorithms::nodeOneOfDisplayCommand(int index) {
	if(_tokens->noMoreTokens(index)) {
		packDisplayCommand();
	} else {
		nodeTwoOfChangeViewTypeCommand(index);
	}
	return;
}


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

void Parser_Algorithms::nodeTwoOfChangeDirectoryCommand(int index) {
	if(_tokens->noMoreTokens(index)) {
		packInvalidCommand();
	} else {
		_description = _tokens->getOriginalToken(index);
		nodeThreeOfChangeDirectoryCommand(index+1);
	}
	return;
}

void Parser_Algorithms::nodeThreeOfChangeDirectoryCommand(int index) {
	if(_tokens->noMoreTokens(index)) {
		packChangeDirectoryCommand();
	} else {
		nodeOneOfAddCommand(START_INDEX);
	}
	return;
}


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

void Parser_Algorithms::nodeThreeOfChangeViewTypeCommand(int index) {
	if(_tokens->noMoreTokens(index)) {
		packChangeViewTypeCommand();
	} else {
		nodeOneOfAddCommand(START_INDEX);
	}
	return;
}


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

void Parser_Algorithms::nodeTwoOfDeleteCommand(int index) {
	if(_tokens->noMoreTokens(index)) {
		packDeleteCommand();
	} else {
		packInvalidCommand();
	}
	return;
}


void Parser_Algorithms::nodeOneOfUndoCommand(int index) {
	if(_tokens->noMoreTokens(index)) {
		packUndoCommand();
	} else {
		nodeOneOfAddCommand(START_INDEX);
	}
	return;
}


void Parser_Algorithms::nodeOneOfExitCommand(int index) {
	if(_tokens->noMoreTokens(index)) {
		packExitCommand();
	} else {
		nodeOneOfAddCommand(START_INDEX);
	}
	return;
}


void Parser_Algorithms::nodeOneOfClearCommand(int index) {
	if(_tokens->noMoreTokens(index)) {
		packClearCommand();
	} else {
		nodeOneOfDeleteCommand(index);
	}
	return;
}


void Parser_Algorithms::nodeOneOfSearchCommand(int index) {
	if(_tokens->noMoreTokens(index)) {
		packInvalidCommand();
	} else {
		_description = _tokens->getOriginalToken(index);
		nodeTwoOfSearchCommand(index+1);
	}
	return;
}

void Parser_Algorithms::nodeTwoOfSearchCommand(int index) {
	if(_tokens->noMoreTokens(index)) {
		packSearchCommand();
	} else {
		nodeOneOfAddCommand(START_INDEX);
	}
	return;
}


void Parser_Algorithms::nodeOneOfAddCommand(int index) {
	Parser_Tasks taskParser(_tokens);
	_task = taskParser.getTask(index);
	packAddCommand();
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
//not integrated
void Parser_Algorithms::packDisplayCommand() {
	_commandPackage = CommandPackage(DISPLAY);
	return;
}

void Parser_Algorithms::packChangeDirectoryCommand() {
	_command = Command_SaveDirectory(_description);
	return;
}

void Parser_Algorithms::packChangeViewTypeCommand() {
	_command = Command_ViewType(_index);
	return;
}

void Parser_Algorithms::packDeleteCommand() {
	_command = Command_Delete(_index);
	return;
}

void Parser_Algorithms::packUndoCommand() {
	_command = Command_Undo();
	return;
}

void Parser_Algorithms::packExitCommand() {
	_command = Command_Exit();
	return;
}

void Parser_Algorithms::packClearCommand() {
	_command = Command_Clear(_indexes);
	return;
}

void Parser_Algorithms::packSearchCommand() {
	_command = Command_Search(_description);
	return;
}

void Parser_Algorithms::packAddCommand() {
	_command = Command_Add(&_task);
	return;
}

void Parser_Algorithms::packEditCommand() {
	_commandPackage = Command_Edit(_index, &_task);
	return;
}
//not integrated
void Parser_Algorithms::packInvalidCommand() {
	_commandPackage = CommandPackage(INVALID);
	return;
}