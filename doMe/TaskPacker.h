#pragma once
#include "Task.h"
#include "InputTokens.h"
#include "ChronoInterpreter.h"
#include "Exception_ExceededParameterLimit.h"
#include <string>
#include <assert.h>

#define BLANK_SPACE " " 
#define LOCATION_MARKER "location"
#define NAME_MARKER "name"

using namespace std;

class TaskPacker
{
public:
	~TaskPacker(void);
	static TaskPacker* getInstance();
	Task* packTask(InputTokens* tokens, int index);

private:
	TaskPacker(void);
	static TaskPacker* _theOne;
	
	InputTokens* _tokens;
	ChronoInterpreter* _chronoInterpreter;

	string _name;
	vector<int> _dates;
	vector<int> _times;
	int _date1;
	int _date2;
	int _time1;
	int _time2;
	string _location;

	void setAttributes(InputTokens* tokens);
	void findTaskDetails(int index);

	void findDateAndTime(int index);
	void findLocation(int index);
	void findName(int index);


	void findDate(int index);
	void extractDates(int index);
	void finalizeDates();
	
	void findTime(int index);
	void extractTimes(int index);
	void finalizeTimes();

	void extractLocation(int index);
	string removeLocationMarker(string s);
	bool hasLocationMarker(string s);

	void extractName(int index);

	string extractStringToBreakPoint(string marker, int index);
};