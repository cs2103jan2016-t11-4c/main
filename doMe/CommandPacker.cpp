//@@author A0122569B

#include "CommandPacker.h"

CommandPacker* CommandPacker::_theOne = NULL;

CommandPacker::CommandPacker() {
	_taskPacker = TaskPacker::getInstance();
	_indexes = new vector<int>;
}

CommandPacker::~CommandPacker(void) {
}

CommandPacker* CommandPacker::getInstance() {
	if(_theOne == NULL) {
		_theOne = new CommandPacker;
	}

	return _theOne;
}


Command* CommandPacker::packCommand(InputTokens* tokens) {
	assert(tokens);

	setEnvironment(tokens);
	branchToNode(START_INDEX);

	return _command;
}


void CommandPacker::setEnvironment(InputTokens* tokens) {
	assert(tokens);

	_tokens = tokens;
	_description = NO_STRING;
	_singleIndex = NO_VALUE;
	delete _indexes;
	_indexes = new vector<int>;
	_isDeleteDate = false;
	_isDeleteTime = false;
	_isDeleteLocation = false;

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
	} else if(_tokens->hasMeaning("REDO", index)) {
		nodeOneOfRedoCommand(index+1);
	} else if(_tokens->hasMeaning("HELP", index)) {
		nodeOneOfHelpCommand(index+1);
	} else if(_tokens->hasMeaning("EXIT", index)) {
		nodeOneOfExitCommand(index+1);
	} else if(_tokens->hasMeaning("SEARCH", index)) {
		nodeOneOfSearchCommand(index+1);
	} else if(_tokens->hasMeaning("CLEAR", index)) {
		nodeOneOfClearCommand(index+1);
	} else if(_tokens->hasMeaning("CHANGEDIRECTORY", index)) {
		nodeThreeOfChangeDirectoryCommand(index+1);
	} else if(_tokens->hasMeaning("CHANGEVIEWTYPE", index)) {
		nodeTwoOfChangeViewTypeCommand(index+1);
	} else {
		nodeOneOfAddCommand(index);
	}
	
	return;
}


void CommandPacker::nodeOneOfDisplayCommand(int index) {
	if(_tokens->isOutOfBounds(index)) {
		packDisplayCommand();
	} else {
		nodeTwoOfChangeViewTypeCommand(index);
	}

	return;
}


void CommandPacker::nodeOneOfChangeDirectoryCommand(int index) {
	if(_tokens->isOutOfBounds(index)) {
		packInvalidCommand();
	} else if(_tokens->hasMeaning("THE", index)) {
		nodeTwoOfChangeDirectoryCommand(index+1);
	} else {
		nodeTwoOfChangeDirectoryCommand(index);
	}

	return;
}

void CommandPacker::nodeTwoOfChangeDirectoryCommand(int index) {
	if(_tokens->isOutOfBounds(index)) {
		packInvalidCommand();
	} else if(_tokens->hasMeaning("DIRECTORY", index)) {
		nodeThreeOfChangeDirectoryCommand(index+1);
	} else {
		nodeOneOfChangeViewTypeCommand(index);
	}

	return;
}

void CommandPacker::nodeThreeOfChangeDirectoryCommand(int index) {
	if(_tokens->isOutOfBounds(index)) {
		packInvalidCommand();
	} else if(_tokens->hasMeaning("TO", index)) {
		nodeFourOfChangeDirectoryCommand(index+1);
	} else {
		nodeFourOfChangeDirectoryCommand(index);
	}

	return;
}

void CommandPacker::nodeFourOfChangeDirectoryCommand(int index) {
	if(_tokens->isOutOfBounds(index)) {
		packInvalidCommand();
	} else {
		_description = _tokens->getOriginalToken(index);
		nodeFiveOfChangeDirectoryCommand(index+1);
	}
	
	return;
}

void CommandPacker::nodeFiveOfChangeDirectoryCommand(int index) {
	if(_tokens->hasNoMoreWord(index)) {
		packChangeDirectoryCommand();
	} else {
		nodeOneOfAddCommand(START_INDEX);
	}
	
	return;
}


void CommandPacker::nodeOneOfChangeViewTypeCommand(int index) {
	if(_tokens->isOutOfBounds(index)) {
		packInvalidCommand();
	} else if(_tokens->hasMeaning("VIEW", index)) {
		nodeTwoOfChangeViewTypeCommand(index+1);
	} else {
		nodeOneOfEditCommand(SECOND_INDEX);
	}
	
	return;
}

void CommandPacker::nodeTwoOfChangeViewTypeCommand(int index) {
	if(_tokens->isOutOfBounds(index)) {
		packInvalidCommand();
	} else if(_tokens->hasMeaning("TO", index)) {
		nodeThreeOfChangeViewTypeCommand(index+1);
	} else {
		nodeThreeOfChangeViewTypeCommand(index);
	}

	return;
}

void CommandPacker::nodeThreeOfChangeViewTypeCommand(int index) {
	if(_tokens->isOutOfBounds(index)) {
		packInvalidCommand();
	} else if(_tokens->isInteger(index)) {
		_singleIndex = stoi(_tokens->getToken(index));
		nodeFourOfChangeViewTypeCommand(index+1);
	} else {
		nodeOneOfAddCommand(START_INDEX);
	}
	
	return;
}

void CommandPacker::nodeFourOfChangeViewTypeCommand(int index) {
	if(_tokens->isOutOfBounds(index)) {
		packChangeViewTypeCommand();
	} else {
		nodeOneOfAddCommand(START_INDEX);
	}
	
	return;
}


void CommandPacker::nodeOneOfDeleteCommand(int index) {
	if(_tokens->isOutOfBounds(index)) {
		_singleIndex = LAST_INDEX;
		packDeleteCommand();
	} else if(_tokens->isInteger(index)) {
		_singleIndex = stoi(_tokens->getToken(index));
		nodeTwoOfDeleteCommand(index+1);
	} else {
		_singleIndex = LAST_INDEX;
		nodeTwoOfDeleteCommand(index);
	}
	
	return;
}

void CommandPacker::nodeTwoOfDeleteCommand(int index) {
	if(_tokens->isOutOfBounds(index)) {
		packDeleteCommand();
	} else if(_tokens->hasMeaning("DELETEPARAMETER", index)) {
		nodeThreeOfDeleteCommand(index);
	} else {
		nodeOneOfClearCommand(SECOND_INDEX);
	}
	
	return;
}

void CommandPacker::nodeThreeOfDeleteCommand(int index) {
	if(_tokens->isOutOfBounds(index)) {
		packDeleteTaskParametersCommand();
	} else if(_tokens->hasMeaning("DELETEPARAMETER", index)) {
		extractDeleteParameter(index);
		nodeThreeOfDeleteCommand(index+1);
	} else {
		nodeOneOfClearCommand(SECOND_INDEX);
	}
	
	return;
}


void CommandPacker::nodeOneOfUndoCommand(int index) {
	if(_tokens->isOutOfBounds(index)) {
		packUndoCommand();
	} else {
		nodeOneOfAddCommand(START_INDEX);
	}
	
	return;
}


void CommandPacker::nodeOneOfRedoCommand(int index) {
	if(_tokens->isOutOfBounds(index)) {
		packRedoCommand();
	} else {
		nodeOneOfAddCommand(START_INDEX);
	}
	
	return;
}


void CommandPacker::nodeOneOfHelpCommand(int index) {
	if(_tokens->isOutOfBounds(index)) {
		packHelpCommand();
	} else {
		nodeOneOfAddCommand(START_INDEX);
	}
	
	return;
}


void CommandPacker::nodeOneOfExitCommand(int index) {
	if(_tokens->isOutOfBounds(index)) {
		packExitCommand();
	} else {
		nodeOneOfAddCommand(START_INDEX);
	}
	
	return;
}


void CommandPacker::nodeOneOfClearCommand(int index) {
	if(_tokens->isOutOfBounds(index)) {
		packClearCommand();
	} else {
		nodeTwoOfClearCommand(index);
	}
	
	return;
}

void CommandPacker::nodeTwoOfClearCommand(int index) {
	assert(!_tokens->isOutOfBounds(index));

	if(_tokens->hasMeaning("ALL", index)) {
		nodeThreeOfClearCommand(index+1);
	} else {
		nodeFourOfClearCommand(index);
	}
	
	return;
}

void CommandPacker::nodeThreeOfClearCommand(int index) {
	if(_tokens->isOutOfBounds(index)) {
		packClearCommand();
	} else {
		nodeOneOfAddCommand(START_INDEX);
	}

	return;
}

void CommandPacker::nodeFourOfClearCommand(int index) {
	assert(!_tokens->isOutOfBounds(index));
	
	if(_tokens->isInteger(index)) {
		addToIndexes(_tokens->getInteger(index));
		nodeFiveOfClearCommand(index+1);
	} else {
		nodeOneOfAddCommand(START_INDEX);
	}
	
	return;
}

void CommandPacker::nodeFiveOfClearCommand(int index) {
	if(_tokens->isOutOfBounds(index)) {
		packClearCommand();
	} else if(_tokens->isInteger(index)) {
		addToIndexes(_tokens->getInteger(index));
		nodeFiveOfClearCommand(index+1);
	} else if(_tokens->hasMeaning("TO", index)) {
		nodeSixOfClearCommand(index+1);
	} else {
		nodeOneOfAddCommand(START_INDEX);
	}
	
	return;
}

void CommandPacker::nodeSixOfClearCommand(int index) {
	if(_tokens->isOutOfBounds(index)) {
		packInvalidCommand();
	} else if(_tokens->isInteger(index)) {
		addRangeToIndexes(_tokens->getInteger(index));
		nodeFiveOfClearCommand(index+1);
	} else {
		nodeOneOfAddCommand(START_INDEX);
	}
	
	return;
}


void CommandPacker::nodeOneOfSearchCommand(int index) {
	if(_tokens->hasNoMoreWord(index)) {
		packInvalidCommand();
	} else if(_tokens->hasMeaning("FOR", index)) {
		nodeTwoOfSearchCommand(index+1);
	} else {
		nodeTwoOfSearchCommand(index);
	}

	return;
}

void CommandPacker::nodeTwoOfSearchCommand(int index) {
	if(_tokens->hasNoMoreWord(index)) {
		packInvalidCommand();
	} else {
		_description = _tokens->getOriginalToken(index);
		nodeThreeOfSearchCommand(index+1);
	}
	
	return;
}

void CommandPacker::nodeThreeOfSearchCommand(int index) {
	if(_tokens->hasNoMoreWord(index)) {
		packSearchCommand();
	} else {
		nodeOneOfAddCommand(START_INDEX);
	}
	
	return;
}


void CommandPacker::nodeOneOfAddCommand(int index) {	
	try {
		_task = _taskPacker->packAddTask(_tokens, index);
		packAddCommand();
	} catch (Exception_ExceededParameterLimit e) {
		packInvalidCommand();
	}
	
	return;
}


void CommandPacker::nodeOneOfEditCommand(int index) {
	if(_tokens->isOutOfBounds(index)) {
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
	if(_tokens->isOutOfBounds(index)) {
		packInvalidCommand();
	} else if(_tokens->hasMeaning("TO", index)) {
		nodeThreeOfEditCommand(index+1);
	} else {
		nodeThreeOfEditCommand(index);
	}

	return;
}

void CommandPacker::nodeThreeOfEditCommand(int index) {
	if(_tokens->isOutOfBounds(index)) {
		packInvalidCommand();
	} else {
		try {
			_task = _taskPacker->packEditTask(_tokens, index);
			packEditCommand();
		} catch (Exception_ExceededParameterLimit e) {
			packInvalidCommand();
		}
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

void CommandPacker::packDeleteTaskParametersCommand() {
	packDeleteTask();
	_command = new Command_Edit(_singleIndex, _task);
	
	return;
}

void CommandPacker::packUndoCommand() {
	_command = new Command_Undo();
	
	return;
}

void CommandPacker::packRedoCommand() {
	_command = new Command_Redo();
	
	return;
}

void CommandPacker::packHelpCommand() {
	_command = new Command_Help();
	
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


void CommandPacker::extractDeleteParameter(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->hasMeaning("DELETEPARAMETER", index));

	if(_tokens->hasMeaning("DATE", index)) {
		_isDeleteDate = true;
	} else if(_tokens->hasMeaning("TIME", index)) {
		_isDeleteTime = true;
	} else if(_tokens->hasMeaning("LOCATION", index)) {
		_isDeleteLocation = true;
	}
	
	assert(false); //method should return before reaching this line
	return;
}

void CommandPacker::packDeleteTask() {
	string name = NO_NAME;
	int date = NO_DATE_DETECTED;
	int time = NO_TIME_DETECTED;
	string location = NO_LOCATION_DETECTED;
	int doneStatus = NO_DONE_DETECTED;
	
	if(_isDeleteTime) {
		time = NO_TIME;
	}
	if(_isDeleteDate) {
		date = NO_DATE;
	}
	if(_isDeleteLocation) {
		location = NO_LOCATION;
	}

	_task = new Task(name, date, date, time, time, location, doneStatus);

	return;
}

void CommandPacker::addToIndexes(int index) {
	vector<int>& indexRef = *_indexes;

	for(unsigned int i = 0; i < indexRef.size();) {
		if(indexRef[i] == index) {
			indexRef.erase(indexRef.begin()+i);
		} else {
			i++;
		}
	}

	indexRef.push_back(index);
}

void CommandPacker::addRangeToIndexes(int index) {
	vector<int>& indexRef = *_indexes;
	int start = indexRef[indexRef.size()-1];
	int end = index;

	if(end < start) {
		end = start;
		start = index;
	}

	for(int i = start; i <= end; i++) {
		addToIndexes(i);
	}

	return;
}