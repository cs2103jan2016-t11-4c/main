//@@author A0130475L
#pragma once
#include "ViewType.h"
#include "ViewType1.h"

class ViewType2 : public ViewType {
private:
    static const string MESSAGE_DISPLAY_HEADER[];
    static const string MESSAGE_TIMING_SEPERATOR;
    static const string MESSAGE_AM;
    static const string MESSAGE_PM;
    static const int TIME_STRING_INT;
    static const int TIME_MIDDAY;

    static const string MESSAGE_MONTH_JANUARY;
    static const string MESSAGE_MONTH_FEBUARY;
    static const string MESSAGE_MONTH_MARCH;
    static const string MESSAGE_MONTH_APRIL;
    static const string MESSAGE_MONTH_MAY;
    static const string MESSAGE_MONTH_JUNE;
    static const string MESSAGE_MONTH_JULY;
    static const string MESSAGE_MONTH_AUGUST;
    static const string MESSAGE_MONTH_SEPTEMPER;
    static const string MESSAGE_MONTH_NOVEMBER;
    static const string MESSAGE_MONTH_DECEMBER;

    static const string MESSAGE_MONTH[];

    //overiding functions
    bool isInNextCategory(Task* individualTask, int i);
    vector<string> getCategoryHeader();
   
public:
    ViewType2(void);
    ViewType2(list<Task*> *taskList);
    ViewType2(list<Task*> *taskList, int currentDate);
    ~ViewType2(void);

    string getDateTaskString(int date);
    string getTimeTaskString(int time);
    string getMonth(int date);

};

