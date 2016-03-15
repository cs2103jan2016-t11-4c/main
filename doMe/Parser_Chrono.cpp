#include "Parser_Chrono.h"


Parser_Chrono::Parser_Chrono(CommandTokens* tokens) :
	_tokens(tokens)
{
	clearCache();
}


Parser_Chrono::~Parser_Chrono(void)
{
}

void Parser_Chrono::interpretDateAndTime(int index) {
	for(int i = index; i < _tokens->getSize(); i++) {
		if(_tokens->isInteger(i)) {
			integerNode(i);
		}
	}
}

void Parser_Chrono::integerNode(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->isInteger(index));
	int size = _tokens->getSize(index);
	if(size == 8 || size == 6) {
		dateFormatANodeOne(index, size);
	} else if(size == 4 && !_tokens->isBlank(index)) {
		timeFormatANodeOne(index);
	} else if(size < 3) {
		dateFormatBNodeOne(index);
	}
	return;
}

void Parser_Chrono::timeFormatANodeOne(int index) {
	int number = _tokens->getInteger(index);
	_minute = number % 100;
	_hour = number/100;

	if(isValidTime()) {
		timeFormatANodeTwo(index+1);
		insertTime(index);
	}
	return;
}

void Parser_Chrono::timeFormatANodeTwo(int index) {
	if(!_tokens->isOutOfBounds(index) && _tokens->hasMeaning("HRS", index)) {
		_tokens->remove(index);
	}
	return;
}

void Parser_Chrono::dateFormatANodeOne(int index, int size) {
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

void Parser_Chrono::dateFormatBNodeOne(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->isInteger(index));
	_day = _tokens->getInteger(index);
	if(dateFormatBNodeTwo(index+1)) {
		insertDate(index);
	}
}

bool Parser_Chrono::dateFormatBNodeTwo(int index) {
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

bool Parser_Chrono::dateFormatBNodeThree(int index) {
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

bool Parser_Chrono::dateFormatBNodeFour(int index) {
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

bool Parser_Chrono::dateFormatBNodeFive(int index) {
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

void Parser_Chrono::insertTime(int index) {
	_tokens->markAs(TIME_MARKER, index);
	
	string time = to_string(_hour*100 + _minute);
	_tokens->replaceWith(time, index);
	clearCache();
}

void Parser_Chrono::insertDate(int index) {
	_tokens->markAs(DATE_MARKER, index);
	
	string date = to_string(_year*10000 + _month*100 + _day);
	_tokens->replaceWith(date, index);
	clearCache();
}

bool Parser_Chrono::isValidTime() {
	if (_hour >= 24 || _hour < 0) {
		return false;
	}
	
	if(_minute >= 60 || _minute < 0) {
		return false;
	}
	return true;
}

bool Parser_Chrono::isValidDate() {
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

bool Parser_Chrono::isLeap(int year) {
	if(year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) {
		return true;
	} else {
		return false;
	}
}

void Parser_Chrono::clearCache() {
	_day = NO_VALUE;
	_month = NO_VALUE;
	_year = NO_VALUE;
	_hour = NO_VALUE;
	_minute = NO_VALUE;
	return;
}