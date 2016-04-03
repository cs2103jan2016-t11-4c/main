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


Task* TaskPacker::packTask(InputTokens* tokens, int index) {
	assert(tokens);
	assert(!tokens->isOutOfBounds(index));

	setEnvironment(tokens);
	findTaskDetails(index);
	
//	return new Task(_name, _date1, _date2, _time1, _time2, _location);
	return new Task(_name, _date1, _date2, _time1, _time2, _location, false);
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

	return;
}

void TaskPacker::findTaskDetails(int index) {
	findDateAndTime(index);
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
		_date2 = _dates[0];
	} else if(_dates.size() == 2) {
		_date1 = _dates[0];
		_date2 = _dates[1];
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
		_time2 = _times[0];
		_time1 = NO_TIME;
	} else if(_times.size() == 2) {
		_time1 = _times[0];
		_time2 = _times[1];
	}
	return;
}


void TaskPacker::findLocation(int index) {
	for(unsigned int i = index; i < _tokens->getSize(); i++) {
		if(hasLocationMarker(_tokens->getToken((int) i))) {
			extractLocation((int) i);
			break;
		}
	}
}

void TaskPacker::extractLocation(int index) {
	assert(!_tokens->isOutOfBounds(index));
	string location = extractStringToBreakPoint(LOCATION_MARKER, index);
	_location = removeLocationMarker(location);
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
			break;
		}
	}
}

void TaskPacker::extractName(int index) {
	assert(!_tokens->isOutOfBounds(index));
	string name = extractStringToBreakPoint(NAME_MARKER, index);
	_name = name;
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