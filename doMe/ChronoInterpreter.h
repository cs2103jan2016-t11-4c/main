//@@author A0122569B

#pragma once

#include "InputTokens.h"
#include "Commons.h"
#include <assert.h>
#include <time.h>

#define NO_VALUE 0
#define TIME_MARKER "time"
#define DATE_MARKER "date"

class ChronoInterpreter
{
public:
	~ChronoInterpreter(void);
	static ChronoInterpreter* getInstance();
	void interpretDateAndTime(InputTokens* tokens, int index);
	int dateArithmetics(int days, int date);

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
	int _nextCount;
	bool _isPM;
	bool _isMeridiemTime;
	int _dateCount;
	int _date;
	int _timeCount;
	int _time;

	void setEnvironment(InputTokens* tokens);
	void traverseTokensForIntepretation(int index);
	void removeNaturalLanguageTokens(int index);

	void interpretationNode(int index);
	void integerNode(int index);
	void alphabeticMonthNode(int index);
	void thisNode(int index);
	void nextNode(int index);
	void relationalDateNode(int index);
	void dayOfTheWeekNode(int index);
	void naturalLanguageNode(int index);

	void twoDigitIntegerNode(int index);
	void threeDigitIntegerNode(int index);
	void fourDigitIntegerNode(int index);
	void sixDigitIntegerNode(int index);
	
	//following nodes look at an aspect of each chrono format
	//the area in the [] brackets is the part being checked by the node
	bool timeFormatANodeOne(int index);			//[1330]hrs
	bool timeFormatANodeTwo(int index);			//1330[hrs]

	bool timeFormatBNodeOne(int index);			//[1230]pm
	bool timeFormatBNodeTwo(int index);			//1230[pm]
	
	bool timeFormatCNodeOne(int index);			//[8].00pm
	bool timeFormatCNodeTwo(int index);			//8[.]00pm
	bool timeFormatCNodeThree(int index);		//8.[00]pm
	bool timeFormatCNodeFour(int index);		//8.00[pm]

	bool timeRangeFormatANodeOne(int index);	//[8]-10pm
	bool timeRangeFormatANodeTwo(int index);	//8[-]10pm
	bool timeRangeFormatANodeThree(int index);	//8-[10pm]

	bool timeRangeFormatBNodeOne(int index);	//[8].00-10pm
	bool timeRangeFormatBNodeTwo(int index);	//8[.]00-10pm
	bool timeRangeFormatBNodeThree(int index);	//8.[00]-10pm
	bool timeRangeFormatBNodeFour(int index);	//8.00[-]10pm
	bool timeRangeFormatBNodeFive(int index);	//8.00-[10pm]

	bool dateFormatANodeOne(int index);			//[1]st/2/17
	bool dateFormatANodeTwo(int index);			//1[st]/2/17
	bool dateFormatANodeThree(int index);		//1st[/]2/17
	bool dateFormatANodeFour(int index);		//1st/[2]/17
	bool dateFormatANodeFive(int index);		//1st/2[/]17
	bool dateFormatANodeSix(int index);			//1st/2/[17]

	bool dateFormatBNodeOne(int index);			//[feb]/1st/17
	bool dateFormatBNodeTwo(int index);			//feb[/]1st/17
	bool dateFormatBNodeThree(int index);		//feb/[1]st/17
	bool dateFormatBNodeFour(int index);		//feb/1[st]/17
	bool dateFormatBNodeFive(int index);		//feb/1st[/]17
	bool dateFormatBNodeSix(int index);			//feb/1st/[17]

	bool dateFormatCNodeOne(int index);			//[feb]1st2017
	bool dateFormatCNodeTwo(int index);			//feb[1]st2017
	bool dateFormatCNodeThree(int index);		//feb1[st]2017
	bool dateFormatCNodeFour(int index);		//feb1st[2017]

	bool dateFormatDNodeOne(int index);			//[1]stfeb2017
	bool dateFormatDNodeTwo(int index);			//1[st]feb2017
	bool dateFormatDNodeThree(int index);		//1st[feb]2017
	bool dateFormatDNodeFour(int index);		//1stfeb[2017]

	bool dateFormatENodeOne(int index);			//[this] week
	bool dateFormatENodeTwo(int index);			//[next next next] sun
	bool dateFormatENodeThree(int index);		//[tmr]
	bool dateFormatENodeFour(int index);		//next next next [week]
	bool dateFormatENodeFive(int index);		//this [mon]

	bool dateFormatFNodeOne(int index);			//[12032017]

	bool dateRangeFormatANodeOne(int index);	// 800 [1]st to 10am 2nd feb
	bool dateRangeFormatANodeTwo(int index);	// 800 1[st] to 10am 2nd feb
	bool dateRangeFormatANodeThree(int index);	// 800 1st [to] 10am 2nd feb
	bool dateRangeFormatANodeFour(int index);	// 800 1st to [10am] 2nd feb
	bool dateRangeFormatANodeFive(int index);	// 800 1st to 10am [2nd feb]

	bool dateRangeFormatBNodeOne(int index);	//feb 2nd [2pm] to 1st 800hrs 
	bool dateRangeFormatBNodeTwo(int index);	//feb 2nd 2pm [to] 1st 800hrs 
	bool dateRangeFormatBNodeThree(int index);	//feb 2nd 2pm to [1]st 800hrs 
	bool dateRangeFormatBNodeFour(int index);	//feb 2nd 2pm to 1[st] 800hrs 

	bool naturalLanguageNodeOne(int index);		//[by] tmr
	bool naturalLanguageNodeTwo(int index);		//by [tmr]
	
	int getMonthFromWord(int index);	
	int getDayOfWeekFromWord(int index);
	int getRelationalDateFromWord(int index);

	void insertTime(int index);
	void insertDate(int index);

	void adjustTo24HrsTime();
	int inferYear();
	int inferYear(int twoDigitYear);

	bool isValid24HrsTime();
	bool isValid12HrsTime();
	bool isValidMinutes();
	bool isValidDate();
	bool isLeap(int year);
	bool isYear(int index);
	bool isDaySuffix(int index);

	void clearCache();
};