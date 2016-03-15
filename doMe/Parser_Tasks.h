#pragma once
#include "Task.h"
#include "CommandTokens.h"
#include "Parser_Chrono.h"
#include <string>
#include <assert.h>

#define BLANK_SPACE " " 
#define LOCATION_MARKER "location"
#define NAME_MARKER "name"

using namespace std;

class Parser_Tasks
{
public:
	Parser_Tasks(CommandTokens* tokens);
	~Parser_Tasks(void);
private:
	CommandTokens* _tokens;
	Task _task;
	string _name;
	vector<int> _dates;
	vector<int> _times;
	int _date1;
	int _date2;
	int _time1;
	int _time2;
	string _location;

public:
	Task getTask(int index);
private:
	void findDateAndTime(int index);
	void findLocation(int index);
	void findName(int index);
	void packTask();

	void finalizeDates();
	void finalizeTimes();

	void extractLocation(int index);
	string removeLocationMarker(string s);
	bool hasLocationMarker(string s);

	void extractName(int index);

	string extractStringToBreakPoint(string marker, int index);
};