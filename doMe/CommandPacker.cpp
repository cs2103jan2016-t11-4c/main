#include "CommandPacker.h"

CommandPacker* CommandPacker::_theOne = NULL;

CommandPacker::CommandPacker()
{
	_taskPacker = TaskPacker::getInstance();
}

CommandPacker::~CommandPacker(void)
{
}

CommandPacker* CommandPacker::getInstance() {
	if(_theOne == NULL) {
		_theOne = new CommandPacker;
	}

	return _theOne;
}


Command* CommandPacker::packCommand(InputTokens* tokens) {
	initializeAttributes(tokens);
	branchToNode(START_INDEX);

	return _command;
}


void CommandPacker::initializeAttributes(InputTokens* tokens) {
	_tokens = tokens;
	
	_description = NO_STRING;
	_singleIndex = NO_VALUE;
	if(_indexes != NULL) {
	delete _indexes;
	}
	if(_task != NULL) {
	delete _task;
	}

	return;
}

void CommandPacker::branchToNode(int index) {
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


void CommandPacker::nodeOneOfDisplayCommand(int index) {
	if(_tokens->hasNoMoreWord(index)) {
		packDisplayCommand();
	} else {
		nodeTwoOfChangeViewTypeCommand(index);
	}
	return;
}


void CommandPacker::nodeOneOfChangeDirectoryCommand(int index) {
	if(_tokens->hasNoMoreWord(index)) {
		packInvalidCommand();
	} else if(_tokens->hasMeaning("DIRECTORY", index)) {
		nodeTwoOfChangeDirectoryCommand(index+1);
	} else {
		nodeOneOfChangeViewTypeCommand(index);
	}
	return;
}

void CommandPacker::nodeTwoOfChangeDirectoryCommand(int index) {
	if(_tokens->hasNoMoreWord(index)) {
		packInvalidCommand();
	} else {
		_description = _tokens->getOriginalToken(index);
		nodeThreeOfChangeDirectoryCommand(index+1);
	}
	return;
}

void CommandPacker::nodeThreeOfChangeDirectoryCommand(int index) {
	if(_tokens->hasNoMoreWord(index)) {
		packChangeDirectoryCommand();
	} else {
		nodeOneOfAddCommand(START_INDEX);
	}
	return;
}


void CommandPacker::nodeOneOfChangeViewTypeCommand(int index) {
	if(_tokens->hasNoMoreWord(index)) {
		packInvalidCommand();
	} else if(_tokens->hasMeaning("DISPLAY", index)) {
		nodeTwoOfChangeViewTypeCommand(index+1);
	} else {
		nodeOneOfEditCommand(index);
	}
	return;
}

void CommandPacker::nodeTwoOfChangeViewTypeCommand(int index) {
	if(_tokens->hasNoMoreWord(index)) {
		packInvalidCommand();
	} else if(_tokens->isInteger(index)) {
		_singleIndex = stoi(_tokens->getToken(index));
		nodeThreeOfChangeViewTypeCommand(index+1);
	} else {
		nodeOneOfAddCommand(START_INDEX);
	}
	return;
}

void CommandPacker::nodeThreeOfChangeViewTypeCommand(int index) {
	if(_tokens->hasNoMoreWord(index)) {
		packChangeViewTypeCommand();
	} else {
		nodeOneOfAddCommand(START_INDEX);
	}
	return;
}


void CommandPacker::nodeOneOfDeleteCommand(int index) {
	if(_tokens->hasNoMoreWord(index)) {
		packInvalidCommand();
	} else if(_tokens->isInteger(index)) {
		_singleIndex = stoi(_tokens->getToken(index));
		nodeTwoOfDeleteCommand(index+1);
	} else {
		nodeOneOfAddCommand(START_INDEX);
	}
	return;
}

void CommandPacker::nodeTwoOfDeleteCommand(int index) {
	if(_tokens->hasNoMoreWord(index)) {
		packDeleteCommand();
	} else {
		packInvalidCommand();
	}
	return;
}


void CommandPacker::nodeOneOfUndoCommand(int index) {
	if(_tokens->hasNoMoreWord(index)) {
		packUndoCommand();
	} else {
		nodeOneOfAddCommand(START_INDEX);
	}
	return;
}


void CommandPacker::nodeOneOfExitCommand(int index) {
	if(_tokens->hasNoMoreWord(index)) {
		packExitCommand();
	} else {
		nodeOneOfAddCommand(START_INDEX);
	}
	return;
}


void CommandPacker::nodeOneOfClearCommand(int index) {
	if(_tokens->hasNoMoreWord(index)) {
		packClearCommand();
	} else {
		nodeOneOfDeleteCommand(index);
	}
	return;
}


void CommandPacker::nodeOneOfSearchCommand(int index) {
	if(_tokens->hasNoMoreWord(index)) {
		packInvalidCommand();
	} else {
		_description = _tokens->getOriginalToken(index);
		nodeTwoOfSearchCommand(index+1);
	}
	return;
}

void CommandPacker::nodeTwoOfSearchCommand(int index) {
	if(_tokens->hasNoMoreWord(index)) {
		packSearchCommand();
	} else {
		nodeOneOfAddCommand(START_INDEX);
	}
	return;
}


void CommandPacker::nodeOneOfAddCommand(int index) {
	_task = _taskPacker->packTask(_tokens, index);
	packAddCommand();
	return;
}


void CommandPacker::nodeOneOfEditCommand(int index) {
	if(_tokens->hasNoMoreWord(index)) {
		packInvalidCommand();
	} else if(_tokens->isInteger(index)) {
		_singleIndex = stoi(_tokens->getToken(index));
		nodeTwoOfEditCommand(index+1);
	} else {
		_singleIndex = LAST_INDEX;
		nodeTwoOfEditCommand(index);
	}
	return;
}

void CommandPacker::nodeTwoOfEditCommand(int index) {
	if(_tokens->hasNoMoreWord(index)) {
		packInvalidCommand();
	} else {
		_task = _taskPacker->packTask(_tokens, index);
		packEditCommand();
	}
	return;
}

void CommandPacker::packDisplayCommand() {
	_command = new Command_Exit();
	return;
}

void CommandPacker::packChangeDirectoryCommand() {
	_command = new Command_SaveDirectory(_description);
	return;
}

void CommandPacker::packChangeViewTypeCommand() {
	_command = new Command_ViewType(_singleIndex);
	return;
}

void CommandPacker::packDeleteCommand() {
	_command = new Command_Delete(_singleIndex);
	return;
}

void CommandPacker::packUndoCommand() {
	_command = new Command_Undo();
	return;
}

void CommandPacker::packExitCommand() {
	_command = new Command_Exit();
	return;
}

void CommandPacker::packClearCommand() {
	_command = new Command_Clear(_indexes);
	return;
}

void CommandPacker::packSearchCommand() {
	_command = new Command_Search(_description);
	return;
}

void CommandPacker::packAddCommand() {
	_command = new Command_Add(_task);
	return;
}

void CommandPacker::packEditCommand() {
	_command = new Command_Edit(_singleIndex, _task);
	return;
}

void CommandPacker::packInvalidCommand() {
	_command = new Command_Invalid();
	return;
}