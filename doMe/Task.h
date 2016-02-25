#pragma once
#include <string>

using namespace std;

class Task {
private:
	string _name;
	int _date1;
	int _date2;
	int _time1;
	int _time2;
	string _location;
	
public:
	Task(string name = "", int date1 = 0, int date2 = 0, int time1 = 0, int time2 = 0, string location = "");
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

	virtual string getFirstDate();
	virtual string getTaskString();
};