#pragma once
#include "InputTokens.h"
#include "Chrono.h"
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
	Chrono _chrono;
	int _day;
	int _month;
	int _year;
	int _hour;
	int _minute;

	void setTokens(InputTokens* tokens);
	void traverseTokens(int index);

	void integerNode(int index);
	void alphabeticMonthNode(int index);
	
	void twoDigitIntegerNode(int index);
	void threeDigitIntegerNode(int index);
	void fourDigitIntegerNode(int index);
	void sixDigitIntegerNode(int index, int size);
	
	void timeFormatANodeOne(int index);
	void timeFormatANodeTwo(int index);

	bool timeFormatBNodeOne(int index);
	bool timeFormatBNodeTwo(int index);

	void dateFormatANodeOne(int index, int size);

	bool dateFormatBNodeOne(int index);
	bool dateFormatBNodeTwo(int index);
	bool dateFormatBNodeThree(int index);
	bool dateFormatBNodeFour(int index);
	bool dateFormatBNodeFive(int index);

	bool dateFormatCNodeOne(int index);

	bool dateFormatDNodeOne(int index);
	bool dateFormatDNodeTwo(int index);
	bool dateFormatDNodeThree(int index);
	
	int getMonthFromWord(int index);

	void insertTime(int index);
	void insertDate(int index);
	
	bool isValidTime();
	bool isValidDate();
	bool isLeap(int year);

	void clearCache();
};

