//@@author A0122569B

#include "TaskPacker.h"

TaskPacker* TaskPacker::_theOne = NULL;

TaskPacker::TaskPacker(void) {
	_chronoInterpreter = ChronoInterpreter::getInstance();
}

TaskPacker::~TaskPacker(void) {
}

TaskPacker* TaskPacker::getInstance() {
	if(_theOne == NULL) {
		_theOne = new TaskPacker;
	}

	return _theOne;
}


Task* TaskPacker::packAddTask(InputTokens* tokens, int index) {
	assert(tokens);
	assert(!tokens->isOutOfBounds(index));

	packStandardTask(tokens, index);
	customizeTaskForAddCommand();
	
	return _task;
}

Task* TaskPacker::packEditTask(InputTokens* tokens, int index) {
	assert(tokens);
	assert(!tokens->isOutOfBounds(index));

	packStandardTask(tokens, index);
	customizeTaskForEditCommand();
	
	return _task;
}


void TaskPacker::packStandardTask(InputTokens* tokens, int index) {
	assert(tokens);
	assert(!tokens->isOutOfBounds(index));

	setEnvironment(tokens);
	findTaskDetails(index);
	_task = new Task(_name, _date1, _date2, _time1, _time2, _location, _doneStatus);
	
	return;
}

void TaskPacker::customizeTaskForAddCommand() {
	if(_task->getDate2() == NO_DATE && _task->getTime2() != NO_TIME) {
		_task->setDate2(DATE);
		if(_task->getTime1() == NO_TIME && _task->getTime2() < TIME ) {
			_task->setDate2(ADD_TO_DATE(1, DATE));
		} else if(_task->getTime1() != NO_TIME && 
				  _task->getTime1() < TIME &&
				  _task->getTime2() < TIME) {
			_task->setDate2(ADD_TO_DATE(1, DATE));
		}
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

	if(_task->getDate1() != NO_DATE && _task->getDate1() > _task->getDate2()) {
		int tempTime = _task->getTime2();
		int tempDate = _task->getDate2();
		_task->setTime2(_task->getTime1());
		_task->setDate2(_task->getDate1());
		_task->setTime1(tempTime);
		_task->setDate1(tempDate);
		if(_task->getTime2() == NO_TIME) {
			_task->setTime2(_task->getTime1());
			_task->setTime1(NO_TIME);
		}
	}
	
	if(_task->getDoneStatus() == NO_DONE_DETECTED) {
		_task->setDoneStatus(NO_DONE);
	}

	if(_task->getDate1() == _task->getDate2() && 
	  (_task->getDate1() != -1 || _task->getDate2() != -2)) {
		  _task->setDate1(-1);
	}

	return;
}

void TaskPacker::customizeTaskForEditCommand() {
	
	if(_task->getDate2() != NO_DATE && _task->getTime1() != NO_TIME && _task->getTime1() > _task->getTime2()) {
		if(_task->getDate1() == NO_DATE) {
			_task->setDate1(_task->getDate2());
			_task->setDate2(ADD_TO_DATE(1,_task->getDate2()));
		} else if(_task->getDate1() == _task->getDate2()) {
			_task->setDate1(_task->getDate2());
			_task->setDate2(ADD_TO_DATE(1,_task->getDate2()));
		}
	}

	if(_task->getDate1() != NO_DATE && _task->getDate1() > _task->getDate2()) {
		int tempTime = _task->getTime2();
		int tempDate = _task->getDate2();
		_task->setTime2(_task->getTime1());
		_task->setDate2(_task->getDate1());
		_task->setTime1(tempTime);
		_task->setDate1(tempDate);
		if(_task->getTime2() == NO_TIME) {
			_task->setTime2(_task->getTime1());
			_task->setTime1(NO_DATE);
		}
	}

	if(_task->getDate1() == _task->getDate2() && 
	  (_task->getDate1() != -1 || _task->getDate2() != -2)) {
		  _task->setDate1(-1);
	}
	
	
	if(_task->getTime1() == NO_TIME) {
		_task->setTime1(NO_TIME_DETECTED);
	}
	if(_task->getTime2() == NO_TIME) {
		_task->setTime2(NO_TIME_DETECTED);
	}
	if(_task->getDate1() == NO_DATE) {
		_task->setDate1(NO_DATE_DETECTED);
	}
	if(_task->getDate2() == NO_DATE) {
		_task->setDate2(NO_DATE_DETECTED);
	}
	if(_task->getLocation() == NO_LOCATION) {
		_task->setLocation(NO_LOCATION_DETECTED);
	}

	return;
}

void TaskPacker::setEnvironment(InputTokens* tokens) {
	_tokens = tokens;
	_name = NO_NAME;
	_date1 = NO_DATE;
	_date2 = NO_DATE;
	_time1 = NO_TIME;
	_time2 = NO_TIME;
	_location = NO_LOCATION;
	_dates.clear();
	_times.clear();
	_doneStatus = NO_DONE_DETECTED;

	return;
}

void TaskPacker::findTaskDetails(int index) {
	findDateAndTime(index);
	findDoneStatus(index);
	findLocation(index);
	findName(index);

	return;
}


void TaskPacker::findDateAndTime(int index) {
	_chronoInterpreter->interpretDateAndTime(_tokens, index);
	findTime(index);
	findDate(index);

	return;
}


void TaskPacker::findDate(int index) {
	extractDates(index);
	finalizeDates();
	return;
}

void TaskPacker::extractDates(int index) {
	for(unsigned int i = index; i < _tokens->getSize(); i++) {
		if(_tokens->isMarkedAs(DATE_MARKER, (int) i)) {
			_dates.push_back(stoi(_tokens->getOriginalToken((int) i)));
		}
	}

	return;
}

void TaskPacker::finalizeDates() {
	if(_dates.size() == 0) {
		_date1 = NO_DATE;
		_date2 = NO_DATE;
	} else if(_dates.size() == 1) {
		_date1 = NO_DATE;
		_date2 = _dates[FIRST_INDEX];
	} else if(_dates.size() == 2) {
		_date1 = _dates[FIRST_INDEX];
		_date2 = _dates[SECOND_INDEX];
	} else if(_dates.size() > 2) {
		throw Exception_ExceededParameterLimit();
	}
	return;
}	


void TaskPacker::findTime(int index) {
	extractTimes(index);
	finalizeTimes();
	return;
}

void TaskPacker::extractTimes(int index) {
	for(unsigned int i = index; i < _tokens->getSize(); i++) {
		if(_tokens->isMarkedAs(TIME_MARKER, (int) i)) {
			_times.push_back(stoi(_tokens->getOriginalToken((int) i)));
		}
	}
		return;
}

void TaskPacker::finalizeTimes() {
	if(_times.size() == 0) {
		_time2 = NO_TIME;
		_time1 = NO_TIME;
	} else if(_times.size() == 1) {
		_time2 = _times[FIRST_INDEX];
		_time1 = NO_TIME;
	} else if(_times.size() == 2) {
		_time1 = _times[FIRST_INDEX];
		_time2 = _times[SECOND_INDEX];
	} else if(_times.size() > 2) {
		throw Exception_ExceededParameterLimit();
	}
	return;
}

void TaskPacker::findDoneStatus(int index) {
	for(unsigned int i = index; i < _tokens->getSize(); i++) {
		if(_tokens->isExtensionOfAWord((int) i)) {
			continue;
		} else if(_tokens->hasMeaning("DONE", (int) i)) {
			_doneStatus = DONE;
			_tokens->markAs(DONE_MARKER, (int) i);
			break;
		} else if(_tokens->hasMeaning("UNDONE", (int) i)) {
			_doneStatus = NO_DONE;
			_tokens->markAs(DONE_MARKER, (int) i);
			break;
		} else if(_tokens->hasMeaning("NOT", (int) i)) {
			if(!_tokens->isOutOfBounds((int) i+1) && !_tokens->hasMeaning("DONE", (int) i+1)) {
			_doneStatus = NO_DONE;
			_tokens->markAs(DONE_MARKER, (int) i);
			_tokens->remove((int) i+1);
			break;
			}
		}
	}
}

void TaskPacker::findLocation(int index) {
	for(unsigned int i = index; i < _tokens->getSize(); i++) {
		if(hasLocationMarker(_tokens->getToken((int) i))) {
			extractLocation((int) i);
		}
	}
}

void TaskPacker::extractLocation(int index) {
	assert(!_tokens->isOutOfBounds(index));
	
	string location = extractStringToBreakPoint(LOCATION_MARKER, index);
	if(_location.compare(NO_LOCATION) == 0) {
		_location = removeLocationMarker(location);
	} else if(_location.compare(NO_LOCATION) != 0) {
		throw Exception_ExceededParameterLimit();
	}

	return;
}

string TaskPacker::removeLocationMarker(string s) {
	assert(s[START_INDEX] == '@');
	s.erase(s.begin());
	return s;
}

bool TaskPacker::hasLocationMarker(string s) {
	if(s[START_INDEX] == '@') {
		return true;
	} else {
		return false;
	}
}


void TaskPacker::findName(int index) {
	for(unsigned int i = index; i < _tokens->getSize(); i++) {
		if(!_tokens->isParsed((int) i)) {
			extractName((int) i);
		}
	}
}

void TaskPacker::extractName(int index) {
	assert(!_tokens->isOutOfBounds(index));
	string name = extractStringToBreakPoint(NAME_MARKER, index);
	if(_name == NO_NAME) {
		_name = name;
	} else if(_name.size() < name.size()) {
		_name = name;
	}

	return;
}


string TaskPacker::extractStringToBreakPoint(string marker, int index) {
	assert(!(_tokens->isOutOfBounds(index)));
	string s = _tokens->getOriginalToken(index);
	_tokens->markAs(marker, index);
	for(index++; !_tokens->isBreakPoint(index); index++) {
		if(!_tokens->isExtensionOfAWord(index)) {
			s += BLANK_SPACE;
		}
		s += _tokens->getOriginalToken(index);
		_tokens->markAs(marker, index);
	}
	return s;
}