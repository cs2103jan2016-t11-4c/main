#pragma once
#include "ViewType.h"
#include "ViewType0.h"

class ViewType1 : public ViewType {
private:
    int _headerMarker;

    static const string MESSAGE_DISPLAY_HEADER;
    static const string MESSAGE_TIMING_SEPERATOR;
    static const string MESSAGE_NEW_LINE;
    static const string MESSAGE_AM;
    static const string MESSAGE_PM;
    static const int TIME_MIDDAY;
    static const string MESSAGE_BOX;
    static const int BOX_LENGTH; 

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

    string getComplimentaryString(Task* individualTask);
    string getTimeTaskString(int time);

public:
    ViewType1(void);
    ViewType1(list<Task*> *taskList);
    ViewType1(list<Task*> *taskList, int currentDate);
    ~ViewType1(void);

    string getDateTaskString(int date);
    string getMonth(int date);

};

