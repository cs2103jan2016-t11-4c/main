//@@author A0125290M
#include "Commons.h"

const string Commons::LOG_FILE_NAME = "doMeLog.txt";
const string Commons::TIME_DIVIDER = ":";
const string Commons::LOG_ENTRY = "%02d/%02d/%d %02d:%02d:%02d [%13s] : %s";

const string Commons::DAYS[] = {
    "Sun",
    "Mon",
    "Tues",
    "Wed",
    "Thurs",
    "Fri",
    "Sat"
};

Commons::Commons() {
}

void Commons::log(string file, string message) {
	char buffer[255];
	ofstream writeFile(LOG_FILE_NAME, fstream::app);

	sprintf_s(buffer, LOG_ENTRY.c_str(), DATE_DAY, DATE_MONTH, DATE_YEAR, TIME_HOUR, TIME_MINUTE, TIME_SECOND, trim(file).c_str(), message.c_str());
	writeFile << buffer << endl;
}

int Commons::getWeek_Day() {
	time_t currentTime;
	struct tm localTime;
	time( &currentTime );
	localtime_s(&localTime, &currentTime);

	return localTime.tm_wday;
}

int Commons::getDate() {
	time_t currentTime;
	struct tm localTime;
	time( &currentTime );
	localtime_s(&localTime, &currentTime);

	int day = localTime.tm_mday;
	int month = localTime.tm_mon + 1;
	int year = localTime.tm_year + 1900;

	int date = year * 10000 + month * 100 + day;

	return date;
}

int Commons::getDate_Day() {
	time_t currentTime;
	struct tm localTime;
	time( &currentTime );
	localtime_s(&localTime, &currentTime);

	return localTime.tm_mday;
}

int Commons::getDate_Month() {
	time_t currentTime;
	struct tm localTime;
	time( &currentTime );
	localtime_s(&localTime, &currentTime);

	return localTime.tm_mon + 1;
}

int Commons::getDate_Year() {
	time_t currentTime;
	struct tm localTime;
	time( &currentTime );
	localtime_s(&localTime, &currentTime);

	return localTime.tm_year + 1900;
}

int Commons::getTime_Hour() {
	time_t currentTime;
	struct tm localTime;
	time( &currentTime );
	localtime_s(&localTime, &currentTime);

	return localTime.tm_hour;
}

int Commons::getTime_Minute() {
	time_t currentTime;
	struct tm localTime;
	time( &currentTime );
	localtime_s(&localTime, &currentTime);

	return localTime.tm_min;
}

int Commons::getTime_Second() {
	time_t currentTime;
	struct tm localTime;
	time( &currentTime );
	localtime_s(&localTime, &currentTime);

	return localTime.tm_sec;
}

string Commons::integerToString(int integer) {
	ostringstream word;
	if(integer < 10) {
		word << 0;
	}
	word << integer;

	return word.str();
}

int Commons::addToDate(int days, int date) {
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

int Commons::generateDate(int day, int month, int year) {
	return (day+month*100+year*10000);
}

int Commons::generateTime(int hour, int minute) {
	return hour*100+minute;
}

int Commons::getYear(int date) {
	return date/10000;
}

int Commons::getMonth(int date) {
	return (date/100)%100;
}
	
int Commons::getDay(int date) {
	return date%100;
}

int getHour(int time) {
	return time/100;
}

int getMinute(int time) {
	return time%100;
}

string Commons::trim(string file) {
	size_t found = file.find_last_of("\\");

	file = file.substr(found+1);

	found = file.find_last_of(".");

	return file.substr(0,found);
}
 
//someone?

int Commons::getDayNumber(int date) {
    int dd;
    int mm;
    int yy;
    int dayNumber;

    dd = getDay(date);
    mm = getMonth(date);
    yy = getYear(date);

    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    yy -= mm < 3;
    dayNumber = (yy + yy/4 - yy/100 + yy/400 + t[mm-1] + dd) % 7;

    return dayNumber;
}

string Commons::getDateStringDay(int dayNumber) {
    return DAYS[dayNumber];
}
