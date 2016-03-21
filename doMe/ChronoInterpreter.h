#pragma once
#include "InputTokens.h"
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
	int _day;
	int _month;
	int _year;
	int _hour;
	int _minute;

	void setTokens(InputTokens* tokens);
	void traverseTokens(int index);

	void integerNode(int index);
	
	void timeFormatANodeOne(int index);
	void timeFormatANodeTwo(int index);

	void dateFormatANodeOne(int index, int size);

	void dateFormatBNodeOne(int index);
	bool dateFormatBNodeTwo(int index);
	bool dateFormatBNodeThree(int index);
	bool dateFormatBNodeFour(int index);
	bool dateFormatBNodeFive(int index);

	void insertTime(int index);
	void insertDate(int index);
	
	bool isValidTime();
	bool isValidDate();
	bool isLeap(int year);

	void clearCache();
};

