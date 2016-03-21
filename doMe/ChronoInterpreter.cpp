#include "ChronoInterpreter.h"

ChronoInterpreter* _theOne = NULL;

ChronoInterpreter::ChronoInterpreter()
{
}

ChronoInterpreter::~ChronoInterpreter(void)
{
}

ChronoInterpreter* ChronoInterpreter::getInstance() {
	if(_theOne == NULL) {
		_theOne = new ChronoInterpreter;
	}

	return _theOne;
}

void ChronoInterpreter::interpretDateAndTime(InputTokens* tokens, int index) {
	setTokens(tokens);
	traverseTokens(index);
	return;
}

void ChronoInterpreter::setTokens(InputTokens* tokens) {
	_tokens = tokens;
	return;
}

void ChronoInterpreter::traverseTokens(int index) {
	for(int i = index; i < _tokens->getSize(); i++) {
		if(_tokens->isInteger(i)) {
			integerNode(i);
		}
	}
	return;
}

void ChronoInterpreter::integerNode(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->isInteger(index));
	int size = _tokens->getSize(index);
	if(size == 8 || size == 6) {
		dateFormatANodeOne(index, size);
	} else if(size == 4 && !_tokens->isExtensionOfAWord(index)) {
		timeFormatANodeOne(index);
	} else if(size < 3) {
		dateFormatBNodeOne(index);
	}
	return;
}

void ChronoInterpreter::timeFormatANodeOne(int index) {
	int number = _tokens->getInteger(index);
	_minute = number % 100;
	_hour = number/100;

	if(isValidTime()) {
		timeFormatANodeTwo(index+1);
		insertTime(index);
	}
	return;
}

void ChronoInterpreter::timeFormatANodeTwo(int index) {
	if(!_tokens->isOutOfBounds(index) && _tokens->hasMeaning("HRS", index)) {
		_tokens->remove(index);
	}
	return;
}

void ChronoInterpreter::dateFormatANodeOne(int index, int size) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->isInteger(index));
	assert(size == 8 || size == 6);
	int number = _tokens->getInteger(index);
	if(size == 6) {
		_year = number % 100;
		_year +=2000;
		number /= 100;
	} else {
		_year = number % 10000;
		number /= 10000;
	}
	_month = number % 100;
	number /= 100;
	_day = number;

	if(isValidDate()) {
		insertDate(index);
	}
	return;
}

void ChronoInterpreter::dateFormatBNodeOne(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->isInteger(index));
	_day = _tokens->getInteger(index);
	if(dateFormatBNodeTwo(index+1)) {
		insertDate(index);
	}
}

bool ChronoInterpreter::dateFormatBNodeTwo(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	}
	if(_tokens->hasMeaning("DIVIDER", index) && dateFormatBNodeThree(index+1)) {
		_tokens->remove(index);
		return true;
	} else {
		return false;
	}
}

bool ChronoInterpreter::dateFormatBNodeThree(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	}
	if(_tokens->isInteger(index) && _tokens->getSize(index) <= 2) {
		_month = _tokens->getInteger(index);
		if(dateFormatBNodeFour(index+1)) {
			_tokens->remove(index);
			return true;
		}
	}
	return false;
}

bool ChronoInterpreter::dateFormatBNodeFour(int index) {
	if(_tokens->isOutOfBounds(index)) {
		_year = 2016;
		if(isValidDate()) {
			return true;
		}
		return false;
	}
	if(_tokens->hasMeaning("DIVIDER", index) && dateFormatBNodeFive(index+1)) {
		_tokens->remove(index);
		return true;
	} else {
		_year = 2016;
		if(isValidDate()) {
			return true;
		}
		return false;
	}
}

bool ChronoInterpreter::dateFormatBNodeFive(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	}
	int size = _tokens->getSize(index);
	if(_tokens->isInteger(index) && (size == 4 || size == 2)) {
		_year = _tokens->getInteger(index);
		if(size == 2) {
			_year += 2000;
		}
		if(isValidDate()) {
			_tokens->remove(index);
			return true;
		}
		return false;
	}
	return false;
}

void ChronoInterpreter::insertTime(int index) {
	string time = to_string(_hour*100 + _minute);
	_tokens->markAs(TIME_MARKER, time, index);
	clearCache();
}

void ChronoInterpreter::insertDate(int index) {
	string date = to_string(_year*10000 + _month*100 + _day);
	_tokens->markAs(DATE_MARKER, date, index);
	clearCache();
}

bool ChronoInterpreter::isValidTime() {
	if (_hour >= 24 || _hour < 0) {
		return false;
	}
	
	if(_minute >= 60 || _minute < 0) {
		return false;
	}
	return true;
}

bool ChronoInterpreter::isValidDate() {
	static const int daysInEachMonth[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	if(_month > 12) {												//month not possible
		return false;
	} else if(_day > daysInEachMonth[_month]) {						//day exceed the month's limit
		return false;
	} else if((_month == 2 && _day == 29) && (!isLeap(_year))) {	//leap day not in a leap year
		return false;
	} else {
		return true;								
	}
}

bool ChronoInterpreter::isLeap(int year) {
	if(year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) {
		return true;
	} else {
		return false;
	}
}

void ChronoInterpreter::clearCache() {
	_day = NO_VALUE;
	_month = NO_VALUE;
	_year = NO_VALUE;
	_hour = NO_VALUE;
	_minute = NO_VALUE;
	return;
}