#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <list>

#include "Task.h"

using namespace std;

class ViewType {

#ifndef TESTMODE 
protected: 
#else 
public: 
#endif
    list<Task*> *_taskList;
    vector<string> _displayList;
    int _currentDate;
    char buffer[255];

    static const string MESSAGE_DISPLAY_CONTENTS;
    static const string MESSAGE_DATE_SEPERATOR;
    static const string MESSAGE_TIME_SEPERATOR;
    static const string MESSAGE_TIMING_SEPERATOR;
    static const string MESSAGE_VOID_STRING;
    static const string MESSAGE_SPACE_STRING;
    static const string MESSAGE_BRACKETS;
    static const string MESSAGE_FLOATING_TASK;
    static const string MESSAGE_DISPLAY_HEADER;
    static const string MESSAGE_NEW_LINE;
    static const string MESSAGE_EMPTY_LIST;

    string createTaskString(Task* individualTask, int index);
    virtual string getComplimentaryString(Task* individualTask);

    virtual string getTimeTaskString(int time);
    virtual string getDateTaskString(int date);

    string getDay(int date);
    virtual string getMonth(int date);
    string getYear(int date);
    string integerToString(int integer);
    string timeToString(string time);

    string formatTaskString(string name , string date1 , string date2 , string time1 , string time2 , string location);
    string formateDateString(string s1, string s2);
    string formateAddSpace(string s);
    string formateAddBracket(string s);

public:
    ViewType(void);
    ViewType(list<Task*> *taskList);
    ViewType(list<Task*> *taskList, int currentDate);
    ~ViewType(void);

    virtual vector<string> createDisplayList();
    //vector<string> createDisplayList();
    vector<string> createSearchList();
    string getTaskString(Task* individualTask);
};

