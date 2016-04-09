//@@author A0130475L
#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <list>
#include <assert.h>

#include "Commons.h"
#include "Task.h"
#include "Memory.h"

using namespace std;

class ViewType {

#ifndef TESTMODE 
protected: 
#else 
public: 
#endif
    list<Task*> *_taskList;
    vector<string> _colourCoding;
    vector<string> _displayList;
    int _currentDate;
    int _dayToEndOfWeek;
    char buffer[255];

    //overiding functions
    virtual vector<string> getCategoryHeader();
    virtual bool isInNextCategory(Task* individualTask, int i);
    virtual string getTimeTaskString(int time);
    virtual string getDateTaskString(int date);
    virtual string getDay(int date);
    virtual string getMonth(int date);
    virtual string getYear(int date);

    string formatTaskString(string name , string date1 , string date2 , string time1 , string time2 , string location);
    string formateDateString(string s1, string s2);
    string formateAddSpace(string s);
    string formateAddBracket(string s);

    string createTaskString(Task* individualTask, int index);
    string colourCoderTag(Task* individualTask, Task* recentTask);

    string integerToString(int integer);
    string timeToString(string time);

    static const int END_OF_WEEK;
    static const int NO_OF_DAYS_IN_WEEK;
    static const int TIME_STRING_INT;
    static const int TIME_MIDDAY;
    static const string MESSAGE_TODAY;
    static const string MESSAGE_DISPLAY_CONTENTS;
    static const string MESSAGE_DATE_SEPERATOR;
    static const string MESSAGE_TIME_SEPERATOR;
    static const string MESSAGE_TIMING_SEPERATOR;
    static const string MESSAGE_MONTH_SEPERATOR;
    static const string MESSAGE_VOID_STRING;
    static const string MESSAGE_SPACE_STRING;
    static const string MESSAGE_BRACKETS;
    static const string MESSAGE_FLOATING_TASK;
    static const string MESSAGE_DISPLAY_HEADER;
    static const string MESSAGE_NEW_LINE;
    static const string MESSAGE_EMPTY_LIST[];
    static const string MESSAGE_MONTH[];
    static const string MESSAGE_NEXT;
    static const string MESSAGE_AM;
    static const string MESSAGE_PM;
    static const string COLOUR_DEFAULT;
    static const string COLOUR_NEW;
    static const string COLOUR_DONE;
    static const string COLOUR_CATEGORY;

public:
    ViewType(void);
    ViewType(list<Task*> *taskList, int currentDate);
    ~ViewType(void);

    vector<string> createDisplayList();
    vector<string> createSearchList();
    string getTaskString(Task* individualTask);
    vector<string> getColourCoding();
};

