//@@author A0122569B

#pragma once

#include "InputTokens.h"
#include "Commons.h"
#include <assert.h>

#define NO_VALUE 0
#define TIME_MARKER "time"
#define DATE_MARKER "date"

class ChronoInterpreter
{
public:
	~ChronoInterpreter(void);
	static ChronoInterpreter* getInstance();
	void interpretDateAndTime(InputTokens* tokens, int index);

private:
	ChronoInterpreter();
	static ChronoInterpreter* _theOne;

	InputTokens* _tokens;
	Commons* common;
	int _day;
	int _month;
	int _year;
	int _hour;
	int _minute;
	bool isPM;
	bool dateFound;

	void setTokens(InputTokens* tokens);
	void traverseTokens(int index);

	void integerNode(int index);
	void alphabeticMonthNode(int index);
	
	void twoDigitIntegerNode(int index);
	void threeDigitIntegerNode(int index);
	void fourDigitIntegerNode(int index);
	
	bool timeFormatANodeOne(int index);
	bool timeFormatANodeTwo(int index);

	bool timeFormatBNodeOne(int index);
	bool timeFormatBNodeTwo(int index);

	bool dateFormatANodeOne(int index);
	bool dateFormatANodeTwo(int index);
	bool dateFormatANodeThree(int index);
	bool dateFormatANodeFour(int index);
	bool dateFormatANodeFive(int index);
	bool dateFormatANodeSix(int index);

	bool dateFormatBNodeOne(int index);
	bool dateFormatBNodeTwo(int index);
	bool dateFormatBNodeThree(int index);
	bool dateFormatBNodeFour(int index);

	bool dateFormatCNodeOne(int index);
	bool dateFormatCNodeTwo(int index);
	bool dateFormatCNodeThree(int index);
	bool dateFormatCNodeFour(int index);

	bool dateFormatDNodeOne(int index);
	bool dateFormatDNodeTwo(int index);
	bool dateFormatDNodeThree(int index);
	bool dateFormatDNodeFour(int index);

	bool dateRangeFormatANodeOne(int index);
	bool dateRangeFormatANodeTwo(int index);
	bool dateRangeFormatANodeThree(int index);
	bool dateRangeFormatANodeFour(int index);
	
	int getMonthFromWord(int index);

	void insertTime(int index);
	void insertDate(int index);

	int generateTime(int hour, int minute);	
	int generateDate(int day, int month, int year);

	bool isPossibleYear(int index);

	int inferYear();
	int inferYear(int twoDigitYear);

	void adjustTo24HrsTime();
	

	bool isExtensionOfDay(int index);

	bool isValid24HrsTime();
	bool isValid12HrsTime();
	bool isValidMinutes();
	bool isValidDate();
	bool isLeap(int year);

	void clearCache();
};