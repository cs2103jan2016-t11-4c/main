//@@author A0125290M

#pragma once

#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Task.h"
#include "Command.h"
#include "Exception_InvalidCommand.h"
#include "Exception_ExceededParameterLimit.h"
#include "Exception_FileCannotOpen.h"
#include "Exception_CorruptedFile.h"
using namespace std;

#define WEEK_DAY Commons::getWeek_Day()
#define DATE Commons::getDate()
#define DATE_DAY Commons::getDate_Day()
#define DATE_MONTH Commons::getDate_Month()
#define DATE_YEAR Commons::getDate_Year()
#define TIME_HOUR Commons::getTime_Hour()
#define TIME_MINUTE Commons::getTime_Minute()
#define TIME_SECOND Commons::getTime_Second()
#define ADD_TO_DATE(days, date) Commons::addToDate(days, date)
#define GENERATE_DATE(day, month, year) Commons::generateDate(day, month, year)
#define GENERATE_TIME(hour, minute) Commons::generateTime(hour, minute)
#define GET_DAY(date) Commons::getDay(date)
#define GET_MONTH(date) Commons::getMonth(date)
#define GET_YEAR(date) Commons::getYear(date)
#define GET_MINUTE(time) Commons::getMinute(time)
#define GET_HOUR(time) Commons::getHour(time)
#define LOG(file, message) Commons::log(file, message)


class Commons {
public:
	Commons();

	static const string LOG_FILE_NAME;
	static const string LOG_ENTRY;
	static const string TIME_DIVIDER;

	static void log(string file, string message);

	static int getWeek_Day();		//eg. 2 = Tuesday, 7 = Sunday
	static int getDate();			//eg. 20161128
	static int getDate_Day();		//eg. 2, 14, 30
	static int getDate_Month();		//eg. 2, 7, 12
	static int getDate_Year();		//eg. 2016
	static int getTime_Hour();		//eg. 2, 14, 23
	static int getTime_Minute();		//eg. 2, 14, 56
	static int getTime_Second();		//eg. 2, 14, 56
	
	static int addToDate(int days, int date);				//eg. 4 + 20160330 = 20160403
	static int generateDate(int day, int month, int year);	//eg. 12 3 2016 -> 20160312
	static int generateTime(int hour, int minute);			//eg. 8 14 -> 814
	static int getYear(int date);	//eg. 20160403 -> 2016
	static int getMonth(int date);	//eg. 20160403 -> 4
	static int getDay(int date);	//eg. 20160403 -> 3
	static int getHour(int time);	//eg. 1315 -> 13
	static int getMinute(int time);	//eg. 1315 -> 15

	
	static string integerToString(int integer);
	static string trim(string file);
};