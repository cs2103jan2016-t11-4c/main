#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <list>

#include "Task.h"

using namespace std;

class ViewType {

protected:
    list<Task*> *_taskList;
    vector<string> _displayList;
    int _currentDate;
    char buffer[255];

    static const string MESSAGE_DATE_SEPERATOR;
    static const string MESSAGE_TIME_SEPERATOR;
    static const string MESSAGE_TIMING_SEPERATOR;
    static const string MESSAGE_VOID_STRING;
    static const string MESSAGE_SPACE_STRING;
    static const string MESSAGE_BRACKETS;
    static const string MESSAGE_FLOATING_TASK;
    static const string MESSAGE_DISPLAY_HEADER;
    static const string MESSAGE_NEW_LINE;

public:
    ViewType(void);
    ViewType(list<Task*> *taskList, int currentDate);
    ~ViewType(void);
    vector<string> createDisplayList();
    virtual string getTaskString(Task* individualTask);

    string formatTaskString(string name , string date1 , string date2 , string time1 , string time2 , string location);
    string formateDateString(string s1, string s2);
    string formateAddSpace(string s);
    string formateAddBracket(string s);

    string getTimeTaskString(int time);
    string getDateTaskString(int date);

    string getDay(int date);
    string getMonth(int date);
    string getYear(int date);

};

