//@@author A0130475L
#pragma once
#include "ViewType.h"


class ViewType1 : public ViewType {
private:
    int _headerMarker;

    static const string MESSAGE_DISPLAY_HEADER;
    static const string MESSAGE_NEW_LINE;
    static const string MESSAGE_AM;
    static const string MESSAGE_PM;
    static const int TIME_STRING_INT;
    static const int TIME_MIDDAY;

    //overiding functions
    string getComplimentaryString(Task* individualTask);

public:
    ViewType1(void);
    ViewType1(list<Task*> *taskList);
    ViewType1(list<Task*> *taskList, int currentDate);
    ~ViewType1(void);

    string getTimeTaskString(int time);
};

