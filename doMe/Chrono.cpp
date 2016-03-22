#include "Chrono.h"

Chrono::Chrono() {
}

int Chrono::getCurrentDate() {
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

int Chrono::getCurrentDay() {
	time_t currentTime;
	struct tm *localTime;

	time( &currentTime );                 		// Get the current time
	localTime = localtime( &currentTime );		// Convert the current time to the local time

	int day = localTime->tm_wday;

	return day;
}