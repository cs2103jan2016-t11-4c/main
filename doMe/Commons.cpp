//@@author A0125290M
#include "Commons.h"

const string Commons::LOG_FILE_NAME = "doMeLog.txt";
const string Commons::TIME_DIVIDER = ":";
const string Commons::LOG_ENTRY = "%d/%d/%d %d:%d:%d [%s] : %s";

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

string Commons::trim(string file) {
	size_t found = file.find_last_of("\\");

	file = file.substr(found+1);

	found = file.find_last_of(".");

	return file.substr(0,found);
}