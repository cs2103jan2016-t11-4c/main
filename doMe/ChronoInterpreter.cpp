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

	setEnvironment(tokens);
	traverseTokensForIntepretation(index);
	removeNaturalLanguageTokens(index);

	return;
}

void ChronoInterpreter::setEnvironment(InputTokens* tokens) {
	_tokens = tokens;
	_dateCount = 0;
	_timeCount = 0;
	_time = 0;
	_date = 0;
	clearCache();
	
	return;
}


void ChronoInterpreter::traverseTokensForIntepretation(int index) {
	assert(!_tokens->isOutOfBounds(index));
	
	for(unsigned int i = index; i < _tokens->getSize(); i++) {
		if(_tokens->isExtensionOfAWord((int) i)) {
			continue;
		} else {
			interpretationNode((int) i);
		}
		clearCache();
	}
	
	return;
}

void ChronoInterpreter::removeNaturalLanguageTokens(int index) {
	assert(!_tokens->isOutOfBounds(index));

	for(unsigned int i = index+1; i < _tokens->getSize(); i++) {
		if(_tokens->hasMeaning("PREPOSITION", (int) i)) {
			   naturalLanguageNode((int) i);
		}
	}

	return;
}


void ChronoInterpreter::interpretationNode(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(!_tokens->isExtensionOfAWord(index));

	if(_tokens->isInteger(index)) {
		integerNode(index);
	} else if(_tokens->hasMeaning("MONTHSOFTHEYEAR", index)) {
		alphabeticMonthNode(index);
	} else if(_tokens->hasMeaning("THIS", index)) {
		thisNode(index);
	} else if(_tokens->hasMeaning("NEXT", index)) {
		nextNode(index);
	} else if(_tokens->hasMeaning("RELATIONALDATE", index)) {
		relationalDateNode(index);
	} else if(_tokens->hasMeaning("DAYSOFTHEWEEK", index)) {
		dayOfTheWeekNode(index);
	}

	return;
}

void ChronoInterpreter::integerNode(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->isInteger(index));

	int size = _tokens->getSize(index);
	if(size == 8 || size == 6) {
		sixDigitIntegerNode(index);
	} else if(size > 2 && size <= 4) {
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
	} else if(dateFormatCNodeOne(index)) {
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

	_nextCount = 0;
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
	assert(!_tokens->isOutOfBounds(index));

	naturalLanguageNodeOne(index);

	return;
}


void ChronoInterpreter::twoDigitIntegerNode(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->isInteger(index));
	assert(_tokens->getSize(index) < 3);
	
	if(timeRangeFormatANodeOne(index)) {
	} else if(timeRangeFormatBNodeOne(index)) {
	} else if(dateRangeFormatANodeOne(index)) {
	} else if(timeFormatBNodeOne(index)) {
	} else if(dateFormatANodeOne(index)) {
	} else if(dateFormatDNodeOne(index)) {
	}

	return;
}

void ChronoInterpreter::fourDigitIntegerNode(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->isInteger(index));
	assert(_tokens->getSize(index) <= 4);	
	assert(_tokens->getSize(index) >= 3);
	
	if(timeRangeFormatANodeOne(index)) {
	} else if(timeFormatBNodeOne(index)) {
	} else if(timeFormatANodeOne(index)) {
	}

	return;
}

void ChronoInterpreter::sixDigitIntegerNode(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->isInteger(index));
	assert(_tokens->getSize(index) <= 8);	
	assert(_tokens->getSize(index) >= 6);
	assert(_tokens->getSize(index) != 7);

	dateFormatFNodeOne(index);

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
	if(!isValid24HrsTime()) {
		return false;
	} else if(_tokens->isOutOfBounds(index)) {
		return true;
	} else if(_tokens->hasMeaning("HRS", index)) {
		_tokens->remove(index);
		return true;
	} else if(_tokens->isExtensionOfAWord(index)) {
		return false;
	} else {
		return true;
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
		_isMeridiemTime = true;
		if(_tokens->hasMeaning("PM", index)) {
			_isPM = true;
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
	assert(_tokens->getSize(index) < 3);

	_hour = _tokens->getInteger(index);

	if(timeFormatCNodeTwo(index+1)) {
		insertTime(index);
		return true;
	} else {
		return false;
	}
}

bool ChronoInterpreter::timeFormatCNodeTwo(int index) {
	if(!_tokens->isOutOfBounds(index) && _tokens->hasMeaning("TIMEDIVIDER", index)) {
		if(timeFormatCNodeThree(index+1)) {
			_tokens->remove(index);
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool ChronoInterpreter::timeFormatCNodeThree(int index) {
	if(_tokens->isOutOfBounds(index) || !_tokens->isInteger(index)) {
		return false;
	} else if(_tokens->getSize(index) != 2) {
		return false;
	} else if(_tokens->getSize(index) == 2) {
		_minute = _tokens->getInteger(index);
	} else {
		assert(false);
	}

	if(timeFormatCNodeFour(index+1)) {
		_tokens->remove(index);
		return true;
	} else {
		return false;
	}
}

bool ChronoInterpreter::timeFormatCNodeFour(int index) {
	if(!isValid24HrsTime()) {
		return false;
	} else if(_tokens->isOutOfBounds(index)) {
		return true;
	} else if(_tokens->hasMeaning("HRS", index)) {
		_tokens->remove(index);
		return true;
	} else if(_tokens->hasMeaning("MERIDIEM", index)) {
		if(isValid12HrsTime()) {
			_isMeridiemTime = true;
			if(_tokens->hasMeaning("PM", index)) {
				_isPM = true;
			}
			adjustTo24HrsTime();
			_tokens->remove(index);
			return true;
		} else {
			return false;
		}
	} else if(_tokens->isExtensionOfAWord(index)) {
		return false;
	} else {
		return true;
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

	if(!isValid24HrsTime()) {
		return false;
	} else if(timeRangeFormatANodeTwo(index + 1)) {
		insertTime(index);
		return true;
	} else {
		return false;
	}
}

bool ChronoInterpreter::timeRangeFormatANodeTwo(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	} else if(!_tokens->hasMeaning("RANGE", index)) {
		return false;
	}
	int hour = _hour;
	int minute = _minute;


	if(timeRangeFormatANodeThree(index+1)) {
		if(_isMeridiemTime) {
			if(_hour > 12) {
				_hour -= 12;
			}
			if(_hour == 0) {
				_hour += 12;
			}
			if((_hour < hour) || (_hour == hour && _minute < minute)) {
				_isPM = !_isPM;
			}
			if(hour == 12) {
				_isPM = !_isPM;
			}
			if(_hour == 12) {
				_isPM = !_isPM;
			}
		} else {
			_isPM = false;
			if(hour == 0) {
				hour = 12;
			}
		}
		_hour = hour;
		_minute = minute;
		if(_isMeridiemTime && !isValid12HrsTime()) {
			return false;
		} else {
			adjustTo24HrsTime();
			_tokens->remove(index);
			return true;
		}
	} else {
		return false;
	}
}

bool ChronoInterpreter::timeRangeFormatANodeThree(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	} else if (!_tokens->isInteger(index)) {
		return false;
	}
	int size = _tokens->getSize(index);
	if (size > 4) {
		return false;
	} else if(timeFormatBNodeOne(index)) {
		return true;
	} else if(size > 2) {
		if(timeFormatANodeOne(index)) {
			return true;
		} else {
			return false;
		}
	} else if(size < 3) {
		if(timeFormatCNodeOne(index)) {
			return true;
		} else {
			return false;
		}
	} else {
		assert(false);
		return false;
	}
}

bool ChronoInterpreter::timeRangeFormatBNodeOne(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->isInteger(index));
	assert(_tokens->getSize(index) < 3);

	_hour = _tokens->getInteger(index);

	if(timeRangeFormatBNodeTwo(index+1)) {
		insertTime(index);
		return true;
	} else {
		return false;
	}
}

bool ChronoInterpreter::timeRangeFormatBNodeTwo(int index) {
	if(!_tokens->isOutOfBounds(index) && _tokens->hasMeaning("TIMEDIVIDER", index)) {
		if(timeRangeFormatBNodeThree(index+1)) {
			_tokens->remove(index);
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool ChronoInterpreter::timeRangeFormatBNodeThree(int index) {
	if(_tokens->isOutOfBounds(index) || !_tokens->isInteger(index)) {
		return false;
	} else if(_tokens->getSize(index) != 2) {
		return false;
	}

	_minute = _tokens->getInteger(index);
	if(!isValid24HrsTime()) {
		return false;
	}

	if(timeFormatCNodeFour(index+1)) {
		_tokens->remove(index);
		return true;
	} else {
		return false;
	}
}

bool ChronoInterpreter::timeRangeFormatBNodeFour(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	} else if(!_tokens->hasMeaning("RANGE", index)) {
		return false;
	}

	int hour = _hour;
	int minute = _minute;

	if(timeRangeFormatBNodeFive(index+1)) {
		if(_isMeridiemTime) {
			if(_hour > 12) {
				_hour -= 12;
			}
			if(_hour == 0) {
				_hour += 12;
			}
			if((_hour < hour) || (_hour == hour && _minute < minute)) {
				_isPM = !_isPM;
			}
			if(hour == 12) {
				_isPM = !_isPM;
			}
			if(_hour == 12) {
				_isPM = !_isPM;
			}
		} else {
			_isPM = false;
			if(hour == 0) {
				hour = 12;
			}
		}
		_hour = hour;
		_minute = minute;
		if(_isMeridiemTime && !isValid12HrsTime()) {
			return false;
		} else {
			adjustTo24HrsTime();
			_tokens->remove(index);
			return true;
		}
	} else {
		return false;
	}	
}

bool ChronoInterpreter::timeRangeFormatBNodeFive(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	} else if (!_tokens->isInteger(index)) {
		return false;
	}
	int size = _tokens->getSize(index);
	if (size > 4) {
		return false;
	} else if(timeFormatBNodeOne(index)) {
		return true;
	} else if(size > 2) {
		if(timeFormatANodeOne(index)) {
			return true;
		} else {
			return false;
		}
	} else if(size < 3) {
		if(timeFormatCNodeOne(index)) {
			return true;
		} else {
			return false;
		}
	} else {
		assert(false);
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
	} else if(isDaySuffix(index) && dateFormatANodeThree(index+1)) {
		_tokens->remove(index);
		return true;
	} else {
		return dateFormatANodeThree(index);
	}
}

bool ChronoInterpreter::dateFormatANodeThree(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	} else if(_tokens->hasMeaning("DATEDIVIDER", index) && dateFormatANodeFour(index+1)) {
		_tokens->remove(index);
		return true;
	} else {
		return false;
	}
}

bool ChronoInterpreter::dateFormatANodeFour(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	} else if(_tokens->isInteger(index) && _tokens->getSize(index) <= 2) {
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
	} else if(_tokens->hasMeaning("DATEDIVIDER", index)) {
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
		} else if(size == 4) {
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
	} else if(_tokens->hasMeaning("DATEDIVIDER", index) && dateFormatBNodeThree(index+1)) {
		_tokens->remove(index);
		return true;
	} else {
		return false;
	}
}

bool ChronoInterpreter::dateFormatBNodeThree(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	} else if(_tokens->isInteger(index) && _tokens->getSize(index) <= 2) {
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
	} else if(isDaySuffix(index) && dateFormatBNodeFive(index+1)) {
		_tokens->remove(index);
		return true;
	} else {
		return dateFormatBNodeFive(index);
	}
}

bool ChronoInterpreter::dateFormatBNodeFive(int index) {
	if(_tokens->isOutOfBounds(index)) {
		_year = inferYear();
	} else if(_tokens->hasMeaning("DATEDIVIDER", index)) {
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
		} else if(size == 4){
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
	} else if(isDaySuffix(index) && dateFormatCNodeFour(index+1)) {
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
	} else if(isYear(index)) {
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
	} else if(isDaySuffix(index) && dateFormatDNodeThree(index+1)) {
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
	} else if(isYear(index)) {
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
		int date = ADD_TO_DATE(daysToTarget, DATE);
		_day = GET_DAY(date);
		_month = GET_MONTH(date);
		_year = GET_YEAR(date);
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
		int date = ADD_TO_DATE(daysToTarget, DATE);
		_day = GET_DAY(date);
		_month = GET_MONTH(date);
		_year = GET_YEAR(date);
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
		int date = ADD_TO_DATE(daysToTarget, DATE);
		_day = GET_DAY(date);
		_month = GET_MONTH(date);
		_year = GET_YEAR(date);
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


bool ChronoInterpreter::dateFormatFNodeOne(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->isInteger(index));
	int size = _tokens->getSize(index);	
	assert(size == 8 || size == 6);

	int number = _tokens->getInteger(index);
	if(size == 6) {
		_year = inferYear(number % 100);
		number /= 100;
	} else if(size == 8) {
		_year = number % 10000;
		number /= 10000;
	} else {
		return false;
	}
	_month = number % 100;
	_day = number/100;

	if(isValidDate()) {
		insertDate(index);
		return true;
	} else {
		return false;
	}
}


bool ChronoInterpreter::dateRangeFormatANodeOne(int index) {
	assert(!_tokens->isOutOfBounds(index));
	assert(_tokens->isInteger(index));
	assert(_tokens->getSize(index) < 3);
	
	_day = _tokens->getInteger(index);
	if(dateRangeFormatANodeTwo(index + 1)) {
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

	if(isDaySuffix(index) && dateRangeFormatANodeThree(index+1)) {
		_tokens->remove(index);
		return true;
	} else {
		return dateRangeFormatANodeThree(index);
	}
}

bool ChronoInterpreter::dateRangeFormatANodeThree(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	} else if(!_tokens->hasMeaning("RANGE", index)) {
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
	} else if(_tokens->getSize(index) > 4) {
		return dateRangeFormatANodeFive(index);
	}
	
	int size = _tokens->getSize(index);
	if(timeFormatBNodeOne(index)) {
		return dateRangeFormatANodeFive(index+1);
	} else if(size > 2) {
		if(timeFormatANodeOne(index)) {
			return dateRangeFormatANodeFive(index+1);
		} else {
			return dateRangeFormatANodeFive(index);
		}
	} else if(size < 3) {
		if(timeFormatCNodeOne(index)) {
			return dateRangeFormatANodeFive(index+1);
		} else {
			return dateRangeFormatANodeFive(index);
		}
	} else {
		assert(false);
		return false;
	}
}

bool ChronoInterpreter::dateRangeFormatANodeFive(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	} else if(!_tokens->isInteger(index)) {
		return false;
	}
	int day = _day;
	int size = _tokens->getSize(index);
	if(size < 3) {
		if(dateFormatANodeOne(index) ||
		   dateFormatDNodeOne(index)) {
			_day = day;
			if(isValidDate()) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else if(size == 6 || size == 8) {
		if(dateFormatFNodeOne(index)) {
			_day = day;
			if(isValidDate()) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else {
		return false;
	}
}


bool ChronoInterpreter::dateRangeFormatBNodeOne(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	} else if(!_tokens->hasMeaning("RANGE", index)) {
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
	} else if(_tokens->getSize(index) > 4) {
		return dateRangeFormatBNodeThree(index);
	}
	
	int size = _tokens->getSize(index);
	if(timeFormatBNodeOne(index)) {
		return dateRangeFormatBNodeThree(index+1);
	} else if(size > 2) {
		if(timeFormatANodeOne(index)) {
			return dateRangeFormatBNodeThree(index+1);
		} else {
			return dateRangeFormatBNodeThree(index);
		}
	} else if(size < 3) {
		if(timeFormatCNodeOne(index)) {
			return dateRangeFormatBNodeThree(index+1);
		} else {
			return dateRangeFormatBNodeThree(index);
		}
	} else {
		assert(false);
		return false;
	}
}

bool ChronoInterpreter::dateRangeFormatBNodeThree(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	} else if (!_tokens->isInteger(index)) {
		return false;
	} else if (_tokens->getSize(index) > 2) {
		return false;
	}
	
	int previousDay = _day;
	_day = _tokens->getInteger(index);
	if(isValidDate()) {
		dateRangeFormatBNodeFour(index+1);
		insertDate(index);
		_day = previousDay;
		return true;
	} else {
		_day = previousDay;
		return false;
	}
}

bool ChronoInterpreter::dateRangeFormatBNodeFour(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	} else if(isDaySuffix(index)) {
		_tokens->remove(index);
		return true;
	} else {
		return false;
	}
}


bool ChronoInterpreter::naturalLanguageNodeOne(int index) {
	assert(!_tokens->isOutOfBounds(index));

	if(naturalLanguageNodeTwo(index+1)) {
		_tokens->remove(index);
		return true;
	} else {
		return false;
	}
}

bool ChronoInterpreter::naturalLanguageNodeTwo(int index) {
	if(_tokens->isOutOfBounds(index)) {
		return false;
	} else if(_tokens->isMarkedAs(DATE_MARKER, index) ||
			  _tokens->isMarkedAs(TIME_MARKER, index)) {
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
	int time = GENERATE_TIME(_hour, _minute);
	_tokens->markAs(TIME_MARKER, to_string(time), index);
	_time = time;
	_timeCount++;
	
	return;
}

void ChronoInterpreter::insertDate(int index) {
	int date = GENERATE_DATE(_day, _month, _year);
	_tokens->markAs(DATE_MARKER, to_string(date), index);
	_date = date;
	_dateCount++;
	
	return;
}


void ChronoInterpreter::adjustTo24HrsTime() {
	if(_isPM && _hour != 12) {
			_hour+=12;
	} else if(!_isPM && _hour == 12) {
			_hour = 0;
	}

	return;
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
	
	if(_month > 12 || _month < 1) {									//month not possible
		return false;
	} else if(_day > daysInEachMonth[_month] || _day < 1) {			//day exceed the month's limit
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

bool ChronoInterpreter::isYear(int index) {
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
	   _tokens->hasMeaning("DATEDIVIDER", index+1)) {
		return false;
	} else {
		return true;
	}
}

bool ChronoInterpreter::isDaySuffix(int index) {
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


void ChronoInterpreter::clearCache() {
	_nextCount = NO_VALUE;
	_isPM = false;
	_isMeridiemTime = false;

	return;
}