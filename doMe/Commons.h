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
#define GET_DAY(date) Commons::getDay(date)
#define GET_MONTH(date) Commons::getMonth(date)
#define GET_YEAR(date) Commons::getYear(date)
#define LOG(file, message) Commons::log(file, message)


class Commons {
public:
	Commons();

	static const string LOG_FILE_NAME;
	static const string LOG_ENTRY;
	static const string TIME_DIVIDER;

	static void log(string file, string message);

	static int getWeek_Day();		//eg. 2 = Tuesday
	static int getDate();			//eg. 20161128
	static int getDate_Day();		//eg. 2, 14, 30
	static int getDate_Month();		//eg. 2, 14, 30
	static int getDate_Year();		//eg. 2016
	static int getTime_Hour();		//eg. 2, 14, 23
	static int getTime_Minute();		//eg. 2, 14, 56
	static int getTime_Second();		//eg. 2, 14, 56
	
	static int addToDate(int days, int date);
	static int generateDate(int day, int month, int year);
	static int getYear(int date);
	static int getMonth(int date);
	static int getDay(int date);
	
	static string integerToString(int integer);
	static string trim(string file);
};