#pragma once
#include <ctime>
using namespace std;

class Chrono {
public:
	Chrono();
	int getCurrentDate();		//YYYYMMDD Format
	int getCurrentDay();		//Monday = 1, Tuesday = 2 etc.
	int getDay(int date);
	int getMonth(int date);
	int getYear(int date);
	int generateDate(int day, int month, int year);
};