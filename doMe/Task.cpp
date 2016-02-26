#include "Task.h"

/*
*  Default constructor and destructor
*/
Task::Task(string name, int date1, int date2, int time1, int time2, string location) {
	_name = name;
	_date1 = date1;
    _date2 = date2;
	_time1 = time1;
    _time2 = time2;
	_location = location;
}

Task::~Task(void) {
}

string Task::getName() {
	return _name;
}
	
int Task::getDate1() {
	return _date1;
}
	
int Task::getDate2() {
	return _date2;
}

int Task::getTime1() {
	return _time1;
}

int Task::getTime2() {
	return _time2;
}

string Task::getLocation() {
	return _location;
}

void Task::setName(std::string newName) {
	_name = newName;
}

void Task::setDate1(int newDate) {
	_date1 = newDate;		
}

void Task::setDate2(int newDate) {
	_date2 = newDate;
}

void Task::setTime1(int newTime) {
	_time1 = newTime;
}

void Task::setTime2(int newTime) {
	_time2 = newTime;
}

void Task::setLocation(std::string newLocation) {
	_location = newLocation;
}






