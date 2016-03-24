#include "ChronoInterpreter.h"

ChronoInterpreter* ChronoInterpreter::_theOne = NULL;

ChronoInterpreter::ChronoInterpreter()
{
	_chrono = Chrono();
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
		} else if(_tokens->hasMeaning("MONTHSOFTHEYEAR", i)) {
			alphabeticMonthNode(i);
		}
	}
	return;
}

void ChronoInterpreter::integerNode(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->isInteger(index));
	if(_tokens->isExtensionOfAWord(index)) {
		return;
	}

	int size = _tokens->getSize(index);
	if(size == 8 || size == 6) {
		sixDigitIntegerNode(index, size);
	} else if(size == 4) {
		fourDigitIntegerNode(index);		
	} else if(size == 3) {
		threeDigitIntegerNode(index);
	} else if(size < 3) {
		twoDigitIntegerNode(index);
	}
	return;
}

void ChronoInterpreter::twoDigitIntegerNode(int index) {
	if(timeFormatBNodeOne(index)) {
		return;
	} else if(dateFormatBNodeOne(index)) {
		return;
	} else {
		dateFormatDNodeOne(index);
	}
}

void ChronoInterpreter::threeDigitIntegerNode(int index) {
	timeFormatBNodeOne(index);
}

void ChronoInterpreter::fourDigitIntegerNode(int index) {
	if(!timeFormatBNodeOne(index)) {
	timeFormatANodeOne(index);
	}
}

void ChronoInterpreter::sixDigitIntegerNode(int index, int size) {
		dateFormatANodeOne(index, size);
}

void ChronoInterpreter::alphabeticMonthNode(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->hasMeaning("MONTHSOFTHEYEAR", index));
	
	_month = getMonthFromWord(index);
	if(dateFormatCNodeOne(index+1)) {
		insertDate(index);
	}
	return;
}

void ChronoInterpreter::timeFormatANodeOne(int index) {
	int number = _tokens->getInteger(index);
	_minute = number % 100;
	_hour = number / 100;

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

bool ChronoInterpreter::timeFormatBNodeOne(int index) {
	int number = _tokens->getInteger(index);
	if(number < 100) {
		_hour = number;
		_minute = 0;
	} else {
	_minute = number % 100;
	_hour = number / 100;
	}

	if(timeFormatBNodeTwo(index+1) && isValidTime()) {
		insertTime(index);
		return true;
	} else {
		return false;
	}
}

bool ChronoInterpreter::timeFormatBNodeTwo(int index) {
	if(_hour > 12 || !isValidTime()) {
		return false;
	} else if(!_tokens->isOutOfBounds(index) && _tokens->hasMeaning("MERIDIEM", index)) {
		if(_tokens->hasMeaning("PM", index) && _hour != 12) {
			_hour+=12;
		}
		if(_tokens->hasMeaning("AM", index) && _hour == 12) {
			_hour = 0;
		}
		_tokens->remove(index);
		return true;
	}
	return false;
}

void ChronoInterpreter::dateFormatANodeOne(int index, int size) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->isInteger(index));
	assert(size == 8 || size == 6);
	int number = _tokens->getInteger(index);
	if(size == 6) {
		_year = number % 100;
		_year +=2000;
		if((_chrono.getYear(_chrono.getCurrentDate()) - 10) > _year) {
			_year +=100;
		}
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

bool ChronoInterpreter::dateFormatBNodeOne(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->isInteger(index));

	_day = _tokens->getInteger(index);
	if(dateFormatBNodeTwo(index+1)) {
		insertDate(index);
		return true;
	}
	return false;
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
		_year = _chrono.getYear(_chrono.getCurrentDate());
		if(isValidDate()) {
			return true;
		}
		return false;
	}
	if(_tokens->hasMeaning("DIVIDER", index) && dateFormatBNodeFive(index+1)) {
		_tokens->remove(index);
		return true;
	} else {
		_year = _chrono.getYear(_chrono.getCurrentDate());
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
			while((_chrono.getYear(_chrono.getCurrentDate()) - 10) > _year) {
				_year +=100;
			}
		}
		if(isValidDate()) {
			_tokens->remove(index);
			return true;
		}
		return false;
	}
	return false;
}

bool ChronoInterpreter::dateFormatCNodeOne(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	}
	if(_tokens->isInteger(index) && _tokens->getSize(index) <= 2) {
		Chrono chrono;
		_day = _tokens->getInteger(index);
		_year = chrono.getYear((chrono.getCurrentDate()));

		if(isValidDate()) {
			dateFormatCNodeTwo(index+1);
			_tokens->remove(index);
			return true;
		}
		return false;
	}
	return false;
}

void ChronoInterpreter::dateFormatCNodeTwo(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return;
	}
	if(_day%10 == 1 && _tokens->hasMeaning("FIRST", index)) {
		_tokens->remove(index);
	} else if(_day%10 == 2 && _tokens->hasMeaning("SECOND", index)) {
		_tokens->remove(index);
	} else if(_day%10 == 3 && _tokens->hasMeaning("THIRD", index)) {
		_tokens->remove(index);
	} else if(_day%10 > 3 && _tokens->hasMeaning("FOURTH", index)) {
		_tokens->remove(index);
	}
}

bool ChronoInterpreter::dateFormatDNodeOne(int index) {
	assert(_tokens->isInteger(index));
	_day = _tokens->getInteger(index);

	if(dateFormatDNodeTwo(index+1)) {
		insertDate(index);
		return true;
	}

	return false;
}

bool ChronoInterpreter::dateFormatDNodeTwo(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	}

	if((_day%10 == 1 && _tokens->hasMeaning("FIRST", index)) ||
       (_day%10 == 2 && _tokens->hasMeaning("SECOND", index)) ||
	   (_day%10 == 3 && _tokens->hasMeaning("THIRD", index)) ||
	   (_day%10 > 3 && _tokens->hasMeaning("FOURTH", index))) {
		if(dateFormatDNodeThree(index+1)) {
			_tokens->remove(index);
			return true;
		} else {
			return false;
		}
	} else {
		return dateFormatDNodeThree(index);
	}
}

bool ChronoInterpreter::dateFormatDNodeThree(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	} else if(_tokens->hasMeaning("MONTHSOFTHEYEAR", index)) {
		_month = getMonthFromWord(index);
		if(dateFormatDNodeFour(index+1)) {
			_tokens->remove(index);
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool ChronoInterpreter::dateFormatDNodeFour(int index) {
	bool yearFound = false;
	if(_tokens->isOutOfBounds(index)) { 
		_year = _chrono.getYear(_chrono.getCurrentDate());
	} else if ((_tokens->isInteger(index)) && 
			  (_tokens->getSize(index) == 2) &&
			  (_tokens->isOutOfBounds(index+1) || 
			  (!_tokens->hasMeaning("MERIDIEM", index+1) && 
			  !_tokens->hasMeaning("MONTHSOFTHEYEAR", index+1) &&
			  !_tokens->isExtensionOfAWord(index+1)))) {
		_year = _tokens->getInteger(index);
		yearFound = true;
		if(_year<100) {
			_year += 2000;
			while((_chrono.getYear(_chrono.getCurrentDate()) - 10) > _year) {
				_year +=100;
			}
		}
	} else {
		_year = _chrono.getYear(_chrono.getCurrentDate());
	}

	if(isValidDate()) {
		if(yearFound) {
		_tokens->remove(index);
		}
		return true;
	}
	return false;
}

int ChronoInterpreter::getMonthFromWord(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->hasMeaning("MONTHSOFTHEYEAR", index));

	if(_tokens->hasMeaning("JANUARY", index)) {
		return 1;
	} else if(_tokens->hasMeaning("FEBRUARY", index)) {
		return 2;
	} else if(_tokens->hasMeaning("MARCH", index)) {
		return 3;
	} else if(_tokens->hasMeaning("APRIL", index)) {
		return 4;
	} else if(_tokens->hasMeaning("MAY", index)) {
		return 5;
	} else if(_tokens->hasMeaning("JUNE", index)) {
		return 6;
	} else if(_tokens->hasMeaning("JULY", index)) {
		return 7;
	} else if(_tokens->hasMeaning("AUGUST", index)) {
		return 8;
	} else if(_tokens->hasMeaning("SEPTEMBER", index)) {
		return 9;
	} else if(_tokens->hasMeaning("OCTOBER", index)) {
		return 10;
	} else if(_tokens->hasMeaning("NOVEMBER", index)) {
		return 11;
	} else if(_tokens->hasMeaning("DECEMBER", index)) {
		return 12;
	}
	
	assert(false); //method should return before reaching this line
	return -1;
}

void ChronoInterpreter::insertTime(int index) {
	string time = to_string(_hour*100 + _minute);
	_tokens->markAs(TIME_MARKER, time, index);
	clearCache();
}

void ChronoInterpreter::insertDate(int index) {
	string date = to_string(_chrono.generateDate(_day, _month, _year));
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
	
	if(_month > 12 || _month < 1) {												//month not possible
		return false;
	} else if(_day > daysInEachMonth[_month] || _day < 1) {						//day exceed the month's limit
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