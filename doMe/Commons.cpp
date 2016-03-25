//@@author A0125290M
#include "Commons.h"

const string Commons::LOG_FILE_NAME = "doMeLog.txt";
const string Commons::TIME_DIVIDER = ":";
const string Commons::LOG_ENTRY = "%d %s [%s] : %s";

Commons::Commons() {
}

void Commons::log(string file, string message) {
	char buffer[255];
	ofstream writeFile(LOG_FILE_NAME, fstream::app);

	sprintf_s(buffer, LOG_ENTRY.c_str(), CURRENT_DATE, CURRENT_TIME.c_str(), trim(file).c_str(), message.c_str());
	writeFile << buffer << endl;
}

string Commons::getCurrentTime() {
	time_t currentTime;
	struct tm *localTime;
	time( &currentTime );                 		// Get the current time
	localTime = localtime( &currentTime );		// Convert the current time

	int hour = localTime->tm_hour;
	int min = localTime->tm_min;
	int sec = localTime->tm_sec;

	string time = integerToString(hour) + TIME_DIVIDER + integerToString(min) + TIME_DIVIDER + integerToString(sec);

	return time;
}

int Commons::getCurrentDate() {
	time_t currentTime;
	struct tm *localTime;
	time( &currentTime );                 		// Get the current time
	localTime = localtime( &currentTime );		// Convert the current time to the local time

	int day    = localTime->tm_mday;
	int month  = localTime->tm_mon + 1;
	int year   = localTime->tm_year + 1900;

	int date = day + month * 100 + year * 10000;	//YYYYMMDD

	return date;
}

int Commons::getCurrentDay() {
	time_t currentTime;
	struct tm *localTime;
	time( &currentTime );                 		// Get the current time
	localTime = localtime( &currentTime );		// Convert the current time to the local time

	int day = localTime->tm_wday;

	return day;
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