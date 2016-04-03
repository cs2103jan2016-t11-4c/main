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
		nodeThreeOfChangeDirectoryCommand(index+1);
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
	} else if(_tokens->hasMeaning("THE", index)) {
		nodeTwoOfChangeDirectoryCommand(index+1);
	} else {
		nodeTwoOfChangeDirectoryCommand(index);
	}

	return;
}

void CommandPacker::nodeTwoOfChangeDirectoryCommand(int index) {
	if(_tokens->hasNoMoreWord(index)) {
		packInvalidCommand();
	} else if(_tokens->hasMeaning("DIRECTORY", index)) {
		nodeThreeOfChangeDirectoryCommand(index+1);
	} else {
		nodeOneOfChangeViewTypeCommand(index);
	}

	return;
}

void CommandPacker::nodeThreeOfChangeDirectoryCommand(int index) {
	if(_tokens->hasNoMoreWord(index)) {
		packInvalidCommand();
	} else if(_tokens->hasMeaning("TO", index)) {
		nodeFourOfChangeDirectoryCommand(index+1);
	} else {
		nodeFourOfChangeDirectoryCommand(index);
	}

	return;
}

void CommandPacker::nodeFourOfChangeDirectoryCommand(int index) {
	if(_tokens->hasNoMoreWord(index)) {
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
	if(_tokens->hasNoMoreWord(index)) {
		packInvalidCommand();
	} else if(_tokens->hasMeaning("VIEW", index)) {
		nodeTwoOfChangeViewTypeCommand(index+1);
	} else {
		nodeOneOfEditCommand(SECOND_INDEX);
	}
	
	return;
}

void CommandPacker::nodeTwoOfChangeViewTypeCommand(int index) {
	if(_tokens->hasNoMoreWord(index)) {
		packInvalidCommand();
	} else if(_tokens->hasMeaning("TO", index)) {
		nodeThreeOfChangeViewTypeCommand(index+1);
	} else {
		nodeThreeOfChangeViewTypeCommand(index);
	}

	return;
}

void CommandPacker::nodeThreeOfChangeViewTypeCommand(int index) {
	if(_tokens->hasNoMoreWord(index)) {
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
	if(_tokens->hasNoMoreWord(index)) {
		packChangeViewTypeCommand();
	} else {
		nodeOneOfAddCommand(START_INDEX);
	}
	
	return;
}


void CommandPacker::nodeOneOfDeleteCommand(int index) {
	if(_tokens->hasNoMoreWord(index)) {
		_singleIndex = LAST_INDEX;
		packDeleteCommand();
	} else if(_tokens->isInteger(index)) {
		_singleIndex = stoi(_tokens->getToken(index));
		nodeTwoOfDeleteCommand(index+1);
	} else {
		nodeOneOfClearCommand(SECOND_INDEX);
	}
	
	return;
}

void CommandPacker::nodeTwoOfDeleteCommand(int index) {
	if(_tokens->hasNoMoreWord(index)) {
		packDeleteCommand();
	} else {
		nodeOneOfClearCommand(SECOND_INDEX);
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
		_task = _taskPacker->packTask(_tokens, index);
		postProcessTask();
		packAddCommand();
	} catch (Exception_ExceededParameterLimit e) {
		packInvalidCommand();
	}
	
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
	} else if(_tokens->hasMeaning("TO", index)) {
		nodeThreeOfEditCommand(index+1);
	} else {
		nodeThreeOfEditCommand(index);
	}

	return;
}

void CommandPacker::nodeThreeOfEditCommand(int index) {
	if(_tokens->hasNoMoreWord(index)) {
		packInvalidCommand();
	} else {
		try {
			_task = _taskPacker->packTask(_tokens, index);
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

void CommandPacker::postProcessTask() {
	if(_task->getDate2() == NO_DATE && _task->getTime2() != NO_TIME) {
		_task->setDate2(DATE);
	}

	if(_task->getTime1() != NO_TIME && _task->getTime1() > _task->getTime2()) {
		if(_task->getDate1() == NO_DATE) {
			_task->setDate1(_task->getDate2());
			_task->setDate2(ADD_TO_DATE(1,_task->getDate2()));
		} else if(_task->getDate1() == _task->getDate2()) {
			_task->setDate1(_task->getDate2());
			_task->setDate2(ADD_TO_DATE(1,_task->getDate2()));
		}
	}

	if(_task->getTime1() != NO_TIME && _task->getDate1() != NO_DATE &&
	   _task->getDate1() > _task->getDate2()) {
		int tempTime = _task->getTime2();
		int tempDate = _task->getDate2();
		_task->setTime2(_task->getTime1());
		_task->setDate2(_task->getTime1());
		_task->setTime1(tempTime);
		_task->setDate1(tempDate);
	}

	return;
}