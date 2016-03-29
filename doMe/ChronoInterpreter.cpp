//@@author A0122569B

#include "ChronoInterpreter.h"

ChronoInterpreter* ChronoInterpreter::_theOne = NULL;

ChronoInterpreter::ChronoInterpreter() {
}

ChronoInterpreter::~ChronoInterpreter(void) {
}

ChronoInterpreter* ChronoInterpreter::getInstance() {
	if(_theOne == NULL) {
		_theOne = new ChronoInterpreter;
	}

	return _theOne;
}

void ChronoInterpreter::interpretDateAndTime(InputTokens* tokens, int index) {
	assert(tokens);
	assert(!tokens->isOutOfBounds(index));

	setTokens(tokens);
	clearCache();
	traverseTokens(index);
	
	return;
}

void ChronoInterpreter::setTokens(InputTokens* tokens) {
	_tokens = tokens;
	
	return;
}

void ChronoInterpreter::traverseTokens(int index) {
	assert(!_tokens->isOutOfBounds(index));
	
	for(unsigned int i = index; i < _tokens->getSize(); i++) {
		if(_tokens->isExtensionOfAWord(i)) {
			continue;
		} else if(_tokens->isInteger((int) i)) {
			integerNode(i);
		} else if(_tokens->hasMeaning("MONTHSOFTHEYEAR", i)) {
			alphabeticMonthNode(i);
		}
		clearCache();
	}
	
	return;
}

void ChronoInterpreter::integerNode(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->isInteger(index));

	int size = _tokens->getSize(index);
	if(size > 2 && size <= 4) {
		fourDigitIntegerNode(index);		
	} else if(size < 3) {
		twoDigitIntegerNode(index);
	}
	
	return;
}

void ChronoInterpreter::twoDigitIntegerNode(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->isInteger(index));
	assert(_tokens->getSize(index) < 3);
	
	if(timeFormatBNodeOne(index)) {
	} else if(dateFormatANodeOne(index)) {
	} else {
		dateFormatDNodeOne(index);
	}
	return;
}


void ChronoInterpreter::fourDigitIntegerNode(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->isInteger(index));
	assert(_tokens->getSize(index) <= 4);	
	assert(_tokens->getSize(index) >= 3);

	if(!timeFormatBNodeOne(index)) {
	timeFormatANodeOne(index);
	}

	return;
}

void ChronoInterpreter::alphabeticMonthNode(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->hasMeaning("MONTHSOFTHEYEAR", index));
	
	if(dateFormatBNodeOne(index)) {
		return;
	} else {
		dateFormatCNodeOne(index);
		return;
	}
}


bool ChronoInterpreter::timeFormatANodeOne(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->isInteger(index));

	int number = _tokens->getInteger(index);
	_minute = number % 100;
	_hour = number / 100;

	if(timeFormatANodeTwo(index+1)) {
		insertTime(index);
		return true;
	} else {
		return false;
	}
}

bool ChronoInterpreter::timeFormatANodeTwo(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	} else if(_tokens->hasMeaning("HRS", index) && isValid24HrsTime()) {
		_tokens->remove(index);
		return true;
	} else {
		return false;
	}
}


bool ChronoInterpreter::timeFormatBNodeOne(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->isInteger(index));

	int number = _tokens->getInteger(index);
	if(number < 100) {
		_hour = number;
		_minute = 0;
	} else {
		_minute = number % 100;
		_hour = number / 100;
	}

	if(timeFormatBNodeTwo(index+1)) {
		insertTime(index);
		return true;
	} else {
		return false;
	}
}

bool ChronoInterpreter::timeFormatBNodeTwo(int index) {
	if(!isValid12HrsTime()) {
		return false;
	} else if(!_tokens->isOutOfBounds(index) && _tokens->hasMeaning("MERIDIEM", index)) {
		if(_tokens->hasMeaning("PM", index)) {
			isPM = true;
		}
		adjustTo24HrsTime();
		_tokens->remove(index);
		return true;
	} else {
		return false;
	}
}


bool ChronoInterpreter::dateFormatANodeOne(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->isInteger(index));
	assert(_tokens->getSize(index) < 3);

	_day = _tokens->getInteger(index);
	if(dateFormatANodeTwo(index+1)) {
		insertDate(index);
		return true;
	} else {
		return false;
	}
}

bool ChronoInterpreter::dateFormatANodeTwo(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	}

	if(isExtensionOfDay(index) && dateFormatANodeThree(index+1)) {
		_tokens->remove(index);
		return true;
	} else {
		return dateFormatANodeThree(index);
	}
}

bool ChronoInterpreter::dateFormatANodeThree(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	}

	if(_tokens->hasMeaning("DIVIDER", index) && dateFormatANodeFour(index+1)) {
		_tokens->remove(index);
		return true;
	} else {
		return false;
	}
}

bool ChronoInterpreter::dateFormatANodeFour(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	}

	if(_tokens->isInteger(index) && _tokens->getSize(index) <= 2) {
		_month = _tokens->getInteger(index);
	} else if (_tokens->hasMeaning("MONTHSOFTHEYEAR", index)) {
		_month = getMonthFromWord(index);
	} else {
		return false;
	}

	if(dateFormatANodeFive(index+1)) {
		_tokens->remove(index);
		return true;
	} else {
		return false;
	}
}

bool ChronoInterpreter::dateFormatANodeFive(int index) {
	if(_tokens->isOutOfBounds(index)) {
		_year = inferYear();
	} else if(_tokens->hasMeaning("DIVIDER", index)) {
		if(dateFormatANodeSix(index+1)) {
			_tokens->remove(index);
			return true;
		} else {
			return false;
		}
	} else {
		_year = inferYear();
	}

	if(isValidDate()) {
		return true;
	} else {
		return false;
	}
}

bool ChronoInterpreter::dateFormatANodeSix(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	}

	unsigned int size = _tokens->getSize(index);
	if(_tokens->isInteger(index) && (size == 4 || size == 2)) {
		if(size == 2) {
			_year = inferYear(_tokens->getInteger(index));
		} else {
			_year = _tokens->getInteger(index);
		}
		if(isValidDate()) {
			_tokens->remove(index);
			return true;
		}
		return false;
	}
	return false;
}


bool ChronoInterpreter::dateFormatBNodeOne(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->hasMeaning("MONTHSOFTHEYEAR", index));

	_month = getMonthFromWord(index);

	if(dateFormatBNodeTwo(index+1)) {
		insertDate(index);
		return true;
	} else {
		return false;
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
		_day = _tokens->getInteger(index);
	} else {
		return false;
	}

	if(dateFormatBNodeFour(index+1)) {
		_tokens->remove(index);
		return true;
	} else {
		return false;
	}
}

bool ChronoInterpreter::dateFormatBNodeFour(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return dateFormatANodeFive(index);
	}

	if(isExtensionOfDay(index) && dateFormatANodeFive(index+1)) {
		_tokens->remove(index);
		return true;
	} else {
		return dateFormatANodeFive(index);
	}
}


bool ChronoInterpreter::dateFormatCNodeOne(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->hasMeaning("MONTHSOFTHEYEAR", index));
	
	_month = getMonthFromWord(index);
	if(dateFormatCNodeTwo(index+1)) {
		insertDate(index);
		return true;
	} else {
		return false;
	}
}

bool ChronoInterpreter::dateFormatCNodeTwo(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	} else if(_tokens->isInteger(index) && _tokens->getSize(index) <= 2) {
		_day = _tokens->getInteger(index);
	} else {
		return false;
	}

	if(dateFormatCNodeThree(index+1)) {
		_tokens->remove(index);
		return true;
	} else {
		return false;
	}
}

bool ChronoInterpreter::dateFormatCNodeThree(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return dateFormatCNodeFour(index);
	}

	if(isExtensionOfDay(index) && dateFormatCNodeFour(index+1)) {
		_tokens->remove(index);
		return true;
	} else {
		return dateFormatCNodeFour(index);
	}
}

bool ChronoInterpreter::dateFormatCNodeFour(int index) {
	bool yearFound = false;
	
	if(_tokens->isOutOfBounds(index)) {
		_year = inferYear();
	} else if(isPossibleYear(index)) {
		yearFound = true;
		_year=_tokens->getInteger(index);
		if(_year < 100) {
			_year = inferYear(_year);
		}
	} else {
		_year = inferYear();
	}

	if(isValidDate()) {
		if(yearFound) {
			_tokens->remove(index);
		}
		return true;
	} else {
		return false;
	}
}


bool ChronoInterpreter::dateFormatDNodeOne(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->isInteger(index));
	assert(_tokens->getSize(index) < 3);

	_day = _tokens->getInteger(index);

	if(dateFormatDNodeTwo(index+1)) {
		insertDate(index);
		return true;
	} else {
		return false;
	}
}

bool ChronoInterpreter::dateFormatDNodeTwo(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	}

	if(isExtensionOfDay(index) && dateFormatDNodeThree(index+1)) {
		_tokens->remove(index);
		return true;
	} else {
		return dateFormatDNodeThree(index);
	}
}

bool ChronoInterpreter::dateFormatDNodeThree(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	} else if(_tokens->hasMeaning("MONTHSOFTHEYEAR", index)) {
		_month = getMonthFromWord(index);
	} else {
		return false;
	}
		
	if(dateFormatCNodeFour(index+1)) {
		_tokens->remove(index);
		return true;
	} else {
		return false;
	}
}

bool ChronoInterpreter::dateRangeFormatANodeOne(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->isInteger(index));
	assert(_tokens->getSize() < 3);
	
	int day = _tokens->getInteger(index);
	_day = day;

	if(dateRangeFormatANodeTwo(index + 1)) {
		_day = day;
		insertDate(index);
		return true;
	} else {
		return false;
	}
}

bool ChronoInterpreter::dateRangeFormatANodeTwo(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	}

	if(isExtensionOfDay(index) && dateRangeFormatANodeThree(index+1)) {
		_tokens->remove(index);
		return true;
	} else {
		return dateRangeFormatANodeThree(index);
	}
}

bool ChronoInterpreter::dateRangeFormatANodeThree(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	} else if(!_tokens->hasMeaning("TO", index)) {
		return false;
	}

	if(dateRangeFormatANodeFour(index+1)) {
		_tokens->remove(index);
		return true;
	} else {
		return false;
	}
}

bool ChronoInterpreter::dateRangeFormatANodeFour(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	} else if (!_tokens->isInteger(index)) {
		return false;
	} else if (_tokens->getSize(index) > 2) {
		return false;
	} else if(_tokens->getInteger(index) < _day) {
		return false;
	} else if(dateFormatANodeOne(index) ||
		      dateFormatDNodeOne(index)) {
		_tokens->remove(index);
		return true;
	} else {
		return false;
	}
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
	string time = to_string(generateTime(_hour,_minute));
	_tokens->markAs(TIME_MARKER, time, index);

	return;
}

void ChronoInterpreter::insertDate(int index) {
	string date = to_string(generateDate(_day, _month, _year));
	_tokens->markAs(DATE_MARKER, date, index);

	return;
}

int ChronoInterpreter::generateTime(int hour, int minute) {
	return (hour*100 + minute);
}

int ChronoInterpreter::generateDate(int day, int month, int year) {
	return (day+month*100+year*10000);
}

bool ChronoInterpreter::isPossibleYear(int index) {
	assert(!_tokens->isOutOfBounds(index));

	if(!_tokens->isInteger(index)) {
		return false;
	} else if(_tokens->getSize(index) != 4 && _tokens->getSize(index) != 2) {
		return false;
	} else if(_tokens->isExtensionOfAWord(index)) {
		return true;
	} else if(_tokens->getSize(index) == 4) {
		return false;
	} else if(_tokens->isOutOfBounds(index+1)) {
		return true;
	} else if(_tokens->hasMeaning("MERIDIEM", index+1) ||
	   _tokens->hasMeaning("MONTHSOFTHEYEAR", index+1) ||
	   _tokens->hasMeaning("DIVIDER", index+1)) {
		return false;
	} else {
		return true;
	}
}

int ChronoInterpreter::inferYear() {
	int year = DATE_YEAR;
	if(DATE_MONTH + 6 > 12 && (DATE_MONTH + 6) % 12 > _month) {
		year++;
	}

	return year;
}

int ChronoInterpreter::inferYear(int twoDigitYear) {
	int year = twoDigitYear + 2000;
	while (DATE_YEAR - 5 > year) {
		year += 100;
	}

	return year;
}

void ChronoInterpreter::adjustTo24HrsTime() {
	if(isPM && _hour != 12) {
			_hour+=12;
	} else if(!isPM && _hour == 12) {
			_hour = 0;
	}

	return;
}

bool ChronoInterpreter::isExtensionOfDay(int index) {
	assert(!_tokens->isOutOfBounds(index));

	if(_day > 3 && _day < 21 && _tokens->hasMeaning("FOURTH", index)) {
		return true;
	} else if(_day > 23 && _day < 31 && _tokens->hasMeaning("FOURTH", index)) {
		return true;
	} else if(_day % 10 == 1 && _tokens->hasMeaning("FIRST", index)) {
		return true;
	} else if(_day%10 == 2 && _tokens->hasMeaning("SECOND", index)) {
		return true;
	} else if(_day%10 == 3 && _tokens->hasMeaning("THIRD", index)) {
		return true;
	} else {
		return false;
	}
}

bool ChronoInterpreter::isValid24HrsTime() {
	if (_hour >= 24 || _hour < 0) {
		return false;
	}
	return isValidMinutes();
}

bool ChronoInterpreter::isValid12HrsTime() {
	if (_hour > 12 || _hour <= 0) {
		return false;
	}
	return isValidMinutes();
}

bool ChronoInterpreter::isValidMinutes() {
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
	isPM = false;
	return;
}