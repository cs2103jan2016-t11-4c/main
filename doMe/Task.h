#pragma once
#include <string>

//Constructor changed for proper default parameterization
//Task object made non-abstract
//I would recommend switching order of parameters to name,time1,date1,time2,date2,location
//Example1: I want make a task about shower by 11 feb 1700hrs
// the object would need to be Task task1("shower",20160211,0,1700);
// if the order is name,time1,date1,time2,date2,location, it's Task task1("shower,1700,20160211);
//example 2: Meeting 11feb 1300-1700
// task("meeting",1300,20160211,1700) vs task("meeting",20160211,0,1300,1700)

using namespace std;

#define NO_DATE 0
#define NO_TIME -1
#define NO_LOCATION ""
#define NO_NAME ""

class Task {
private:
	string _name;
	int _date1;
	int _date2;
	int _time1;
	int _time2;
	string _location;
	
public:
	Task(string name = NO_NAME, int date1 = NO_DATE, int date2 = NO_DATE, int time1 = NO_TIME, int time2 = NO_TIME, string location = NO_LOCATION);
	~Task();
	string getName();
	int getDate1();
	int getDate2();
	int getTime1();
	int getTime2();
	string getLocation();

	void setName(string newName);
	void setDate1(int newDate);
	void setDate2(int newDate);
	void setTime1(int newTime);
	void setTime2(int newTime);
	void setLocation(string newLocation);
};