#include "Parser_Tasks.h"

Parser_Tasks::Parser_Tasks(CommandTokens* tokens) :
_tokens(tokens)
{
	_name = NO_NAME;
	_date1 = NO_DATE;
	_date2 = NO_DATE;
	_time1 = NO_TIME;
	_time2 = NO_TIME;
	_location = NO_LOCATION;
}

Parser_Tasks::~Parser_Tasks(void)
{
}

Task Parser_Tasks::getTask(int index) {
	findDateAndTime(index);
	findLocation(index);
	findName(index);
	packTask();
	return _task;
}

void Parser_Tasks::findDateAndTime(int index) {
	Parser_Chrono chronoParser = Parser_Chrono(_tokens);
	chronoParser.interpretDateAndTime(index);
	for(int i = index; i < _tokens->getSize(); i++) {
		if(_tokens->isMarkedAs(TIME_MARKER, i)) {
			_times.push_back(stoi(_tokens->getOriginalToken(i)));
		}
		if(_tokens->isMarkedAs(DATE_MARKER, i)) {
			_dates.push_back(stoi(_tokens->getOriginalToken(i)));
		}
	}
	finalizeDates();
	finalizeTimes();
}

void Parser_Tasks::finalizeDates() {
	if(_dates.size() == 0) {
		_date1 = NO_DATE;
		_date2 = NO_DATE;
	} else if(_dates.size() == 1) {
		_date1 = NO_DATE;
		_date2 = _dates[0];
	} else if(_dates.size() == 2) {
		_date1 = _dates[0];
		_date2 = _dates[1];
	}
	return;
}

void Parser_Tasks::finalizeTimes() {
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

void Parser_Tasks::findLocation(int index) {
	for(int i = index; i < _tokens->getSize(); i++) {
		if(hasLocationMarker(_tokens->getToken(i))) {
			extractLocation(i);
			break;
		}
	}
}

void Parser_Tasks::extractLocation(int index) {
	assert(!_tokens->isOutOfBounds(index));
	string location = extractStringToBreakPoint(LOCATION_MARKER, index);
	_location = removeLocationMarker(location);
	return;
}

string Parser_Tasks::removeLocationMarker(string s) {
	assert(s[START_INDEX] == '@');
	s.erase(s.begin());
	return s;
}

bool Parser_Tasks::hasLocationMarker(string s) {
	if(s[START_INDEX] == '@') {
		return true;
	} else {
		return false;
	}
}

void Parser_Tasks::findName(int index) {
	for(int i = index; i < _tokens->getSize(); i++) {
		if(!_tokens->isParsed(i)) {
			extractName(i);
			break;
		}
	}
}

void Parser_Tasks::extractName(int index) {
	assert(!_tokens->isOutOfBounds(index));
	string name = extractStringToBreakPoint(NAME_MARKER, index);
	_name = name;
	return;
}

void Parser_Tasks::packTask() {
	_task = Task(_name, _date1, _date2, _time1, _time2, _location);
	return;
}

string Parser_Tasks::extractStringToBreakPoint(string marker, int index) {
	assert(!(_tokens->isOutOfBounds(index)));
	string s = _tokens->getOriginalToken(index);
	_tokens->markAs(marker, index);
	for(index++; !_tokens->isBreakPoint(index); index++) {
	if(!_tokens->isBlank(index)) {
	s += BLANK_SPACE;
	}
	s += _tokens->getOriginalToken(index);
	_tokens->markAs(marker, index);
	}
	return s;
}