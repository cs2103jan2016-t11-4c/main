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
		if(_tokens->isExtensionOfAWord((int) i)) {
			continue;
		} else if(_tokens->isInteger((int) i)) {
			integerNode((int) i);
		} else if(_tokens->hasMeaning("MONTHSOFTHEYEAR", (int) i)) {
			alphabeticMonthNode((int) i);
		} else if(_tokens->hasMeaning("THIS", (int) i)) {
			thisNode((int) i);
		} else if(_tokens->hasMeaning("NEXT", (int) i)) {
			nextNode((int) i);
		} else if(_tokens->hasMeaning("RELATIONALDATE", (int) i)) {
			relationalDateNode((int) i);
		} else if(_tokens->hasMeaning("DAYSOFTHEWEEK", (int) i)) {
			dayOfTheWeekNode((int) i);
		}
		clearCache();
	}
	
	return;
}

void ChronoInterpreter::postProcess(int index) {
	assert(!_tokens->isOutOfBounds(index));

	for(unsigned int i = index+1; i < _tokens->getSize(); i++) {
		if(_tokens->isMarkedAs(DATE_MARKER, (int) i) ||
		   _tokens->isMarkedAs(TIME_MARKER, (int) i)) {
			   naturalLanguageNode((int) i-1);
		}
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

void ChronoInterpreter::alphabeticMonthNode(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->hasMeaning("MONTHSOFTHEYEAR", index));
	
	if(dateFormatBNodeOne(index)) {
	} else {
		dateFormatCNodeOne(index);
	}

		return;
}

void ChronoInterpreter::thisNode(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->hasMeaning("THIS", index));

	dateFormatENodeOne(index);

	return;
}

void ChronoInterpreter::nextNode(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->hasMeaning("NEXT", index));

	dateFormatENodeTwo(index);

	return;
}

void ChronoInterpreter::relationalDateNode(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->hasMeaning("RELATIONALDATE", index));
	
	dateFormatENodeThree(index);

	return;
}

void ChronoInterpreter::dayOfTheWeekNode(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->hasMeaning("DAYSOFTHEWEEK", index));

	dateFormatENodeFive(index);

	return;
}

void ChronoInterpreter::naturalLanguageNode(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return;
	} else if(isReferToTime(index)) {
		_tokens->remove(index);
	}
	
	return;
}

void ChronoInterpreter::twoDigitIntegerNode(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->isInteger(index));
	assert(_tokens->getSize(index) < 3);
	
	if(timeRangeFormatANodeOne(index)) {
	} else if(dateRangeFormatANodeOne(index)) {
	} else if(timeFormatBNodeOne(index)) {
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
	
	if(timeRangeFormatANodeOne(index)) {
	} else if(timeRangeFormatBNodeOne(index)) {
	} else if(timeFormatBNodeOne(index)) {
	} else if(timeFormatCNodeOne(index)) {
	} else {
		timeFormatANodeOne(index);
	}

	return;
}


bool ChronoInterpreter::timeFormatANodeOne(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->isInteger(index));
	assert(_tokens->getSize(index) < 5);
	assert(_tokens->getSize(index) > 2);
	
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
	assert(_tokens->getSize(index) < 5);

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


bool ChronoInterpreter::timeFormatCNodeOne(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->isInteger(index));
	assert(_tokens->getSize(index) < 5);
	assert(_tokens->getSize(index) > 2);
	
	if(_tokens->isOutOfBounds(index-1)) {
		return false;
	} else if (!_tokens->isMarkedAs(DATE_MARKER,index-1)) {
		return false;
	}

	int number = _tokens->getInteger(index);
	_minute = number % 100;
	_hour = number / 100;

	if(isValid24HrsTime()) {
		insertTime(index);
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
	} else {
		return false;
	}
	
	if(isValidDate()) {
		_tokens->remove(index);
		return true;
	} else {
		return false;
	}
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
		return dateFormatBNodeFive(index);
	}

	if(isExtensionOfDay(index) && dateFormatBNodeFive(index+1)) {
		_tokens->remove(index);
		return true;
	} else {
		return dateFormatBNodeFive(index);
	}
}

bool ChronoInterpreter::dateFormatBNodeFive(int index) {
	if(_tokens->isOutOfBounds(index)) {
		_year = inferYear();
	} else if(_tokens->hasMeaning("DIVIDER", index)) {
		if(dateFormatBNodeSix(index+1)) {
			_tokens->remove(index);
			return true;
		} else {
			return false;
		}
	} else {
		_year = inferYear();
	}

	if(isValidDate()) {
		dateRangeFormatBNodeOne(index);
		return true;
	} else {
		return false;
	}
}

bool ChronoInterpreter::dateFormatBNodeSix(int index) {
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
	} else {
		return false;
	}
	
	if(isValidDate()) {
		_tokens->remove(index);
		return true;
	} else {
		return false;
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
		} else {
			dateRangeFormatBNodeOne(index);
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
		
	if(dateFormatDNodeFour(index+1)) {
		_tokens->remove(index);
		return true;
	} else {
		return false;
	}
}

bool ChronoInterpreter::dateFormatDNodeFour(int index) {
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

bool ChronoInterpreter::dateFormatENodeOne(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->hasMeaning("THIS", index));

	if(dateFormatENodeFour(index+1)) {
		_tokens->remove(index);
		return true;
	}

	return false;
}

bool ChronoInterpreter::dateFormatENodeTwo(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	} else if(_tokens->hasMeaning("NEXT", index)) {
		_nextCount++;
		if(dateFormatENodeTwo(index+1)) {
			_tokens->remove(index);
			return true;
		} else {
			return false;
		}
	} else {
		return dateFormatENodeFour(index);
	}
}

bool ChronoInterpreter::dateFormatENodeThree(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	}

	if(_tokens->hasMeaning("RELATIONALDATE", index)) {
		int daysToTarget = getRelationalDateFromWord(index);
		int date = dateArithmetics(daysToTarget, DATE);
		_day = getDay(date);
		_month = getMonth(date);
		_year = getYear(date);
		if(isValidDate()) {
			insertDate(index);
			return true;
		} else {
			return false;
		}
	} else {
		return dateFormatENodeThree(index);
	}
}

bool ChronoInterpreter::dateFormatENodeFour(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	}

	if(_tokens->hasMeaning("WEEK", index)) {
		int daysToTarget = 7 - WEEK_DAY;
		daysToTarget += 7 * _nextCount;
		int date = dateArithmetics(daysToTarget, DATE);
		_day = getDay(date);
		_month = getMonth(date);
		_year = getYear(date);
		if(isValidDate()) {
			insertDate(index);
			return true;
		} else {
			return false;
		}
	} else {
		return dateFormatENodeFive(index);
	}
}

bool ChronoInterpreter::dateFormatENodeFive(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	}

	if(_tokens->hasMeaning("DAYSOFTHEWEEK", index)) {
		int daysToTarget = getDayOfWeekFromWord(index);
		daysToTarget = (daysToTarget + 7 - WEEK_DAY) % 7;
		daysToTarget += 7 * _nextCount;
		int date = dateArithmetics(daysToTarget, DATE);
		_day = getDay(date);
		_month = getMonth(date);
		_year = getYear(date);
		if(isValidDate()) {
			insertDate(index);
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}


bool ChronoInterpreter::timeRangeFormatANodeOne(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->isInteger(index));
	assert(_tokens->getSize(index) < 5);
	
	int number = _tokens->getInteger(index);
	if(number < 100) {
		_hour = number;
		_minute = 0;
	} else {
		_minute = number % 100;
		_hour = number / 100;
	}

	if(!isValid12HrsTime()) {
		return false;
	}
	
	int hour = _hour;
	int minute = _minute;
	if(timeRangeFormatANodeTwo(index + 1)) {
		if(_hour > 12) {
			_hour -= 12;
		}
		if(_hour == 0) {
			_hour += 12;
		}
		if((_hour < hour) || (_hour == hour && _minute < minute)) {
			isPM = !isPM;
		}
		if(hour == 12) {
			isPM = !isPM;
		}
		if(_hour == 12) {
			isPM = !isPM;
		}

		_hour = hour;
		_minute = minute;
		adjustTo24HrsTime();
		insertTime(index);
		return true;
	} else {
		return false;
	}
}

bool ChronoInterpreter::timeRangeFormatANodeTwo(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	} else if(!_tokens->hasMeaning("TO", index)) {
		return false;
	}

	if(timeRangeFormatANodeThree(index+1)) {
		_tokens->remove(index);
		return true;
	} else {
		return false;
	}
}

bool ChronoInterpreter::timeRangeFormatANodeThree(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	} else if (!_tokens->isInteger(index)) {
		return false;
	} else if (_tokens->getSize(index) > 4) {
		return false;
	} else if(timeFormatBNodeOne(index)) {
		return true;
	} else {
		return false;
	}
}


bool ChronoInterpreter::timeRangeFormatBNodeOne(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->isInteger(index));
	assert(_tokens->getSize(index) < 5);
	assert(_tokens->getSize(index) > 2);

	int number = _tokens->getInteger(index);
		_minute = number % 100;
		_hour = number / 100;

	if(!isValid24HrsTime()) {
		return false;
	}
	
	int hour = _hour;
	int minute = _minute;
	if(timeRangeFormatBNodeTwo(index + 1)) {
		_hour = hour;
		_minute = minute;
		insertTime(index);
		return true;
	} else {
		return false;
	}
}

bool ChronoInterpreter::timeRangeFormatBNodeTwo(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	} else if(!_tokens->hasMeaning("TO", index)) {
		return false;
	}

	if(timeRangeFormatBNodeThree(index+1)) {
		_tokens->remove(index);
		return true;
	} else {
		return false;
	}
}

bool ChronoInterpreter::timeRangeFormatBNodeThree(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	} else if (!_tokens->isInteger(index)) {
		return false;
	} else if (_tokens->getSize(index) > 4) {
		return false;
	} else if (_tokens->getSize(index) < 3) {
		return false;
	} else if(timeFormatANodeOne(index)) {
		return true;
	} else {
		return false;
	}
}


bool ChronoInterpreter::dateRangeFormatANodeOne(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->isInteger(index));
	assert(_tokens->getSize(index) < 3);
	
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
		return true;
	} else {
		return false;
	}
}


bool ChronoInterpreter::dateRangeFormatBNodeOne(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	} else if(!_tokens->hasMeaning("TO", index)) {
		return false;
	} else if(dateRangeFormatBNodeTwo(index+1)) {
		_tokens->remove(index);
		return true;
	} else {
		return false;
	}
}

bool ChronoInterpreter::dateRangeFormatBNodeTwo(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	} else if (!_tokens->isInteger(index)) {
		return false;
	} else if (_tokens->getSize(index) > 2) {
		return false;
	} else if(_tokens->getInteger(index) < _day) {
		return false;
	}
	
	int previousDay = _day;
	_day = _tokens->getInteger(index);
	if(isValidDate()) {
		dateRangeFormatBNodeThree(index+1);
		insertDate(index);
		_day = previousDay;
		return true;
	} else {
		_day = previousDay;
		return false;
	}
}

bool ChronoInterpreter::dateRangeFormatBNodeThree(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	} else if(isExtensionOfDay(index)) {
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

int ChronoInterpreter::getDayOfWeekFromWord(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->hasMeaning("DAYSOFTHEWEEK", index));

	if(_tokens->hasMeaning("MONDAY", index)) {
		return 1;
	} else if(_tokens->hasMeaning("TUESDAY", index)) {
		return 2;
	} else if(_tokens->hasMeaning("WEDNESDAY", index)) {
		return 3;
	} else if(_tokens->hasMeaning("THURSDAY", index)) {
		return 4;
	} else if(_tokens->hasMeaning("FRIDAY", index)) {
		return 5;
	} else if(_tokens->hasMeaning("SATURDAY", index)) {
		return 6;
	} else if(_tokens->hasMeaning("SUNDAY", index)) {
		return 7;
	}
	
	assert(false); //method should return before reaching this line
	return -1;
}

int ChronoInterpreter::getRelationalDateFromWord(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->hasMeaning("RELATIONALDATE", index));

	if(_tokens->hasMeaning("TODAY", index)) {
		return 0;
	} else if(_tokens->hasMeaning("TOMORROW", index)) {
		return 1;
	} else if(_tokens->hasMeaning("YESTERDAY", index)) {
		return -1;
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

int ChronoInterpreter::dateArithmetics(int days, int date) {
	int day = getDay(date);
	int month = getMonth(date);
	int year = getYear(date);

	std::tm t = {};
	t.tm_mday = day;
	t.tm_mon = month - 1;
	t.tm_year = year - 1900;
	
	t.tm_mday += days;
	mktime(&t);

	day = t.tm_mday;
	month = t.tm_mon + 1;
	year = t.tm_year + 1900;

	return generateDate(day, month, year);
}

int ChronoInterpreter::generateTime(int hour, int minute) {
	return (hour*100 + minute);
}

int ChronoInterpreter::generateDate(int day, int month, int year) {
	return (day+month*100+year*10000);
}

int ChronoInterpreter::getYear(int date) {
	return date/10000;
}

int ChronoInterpreter::getMonth(int date) {
	return (date/100)%100;
}
	
int ChronoInterpreter::getDay(int date) {
	return date%100;
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

bool ChronoInterpreter::isReferToTime(int index) {
	assert(!_tokens->isOutOfBounds(index));

	if(_tokens->hasMeaning("TO",index)) {
		return true;
	} else if(_tokens->hasMeaning("BY",index)) {
		return true;
	} else if(_tokens->hasMeaning("FROM",index)) {
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
	int daysInEachMonth[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
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
	_nextCount = NO_VALUE;
	isPM = false;

	return;
}