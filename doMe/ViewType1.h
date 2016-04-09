//@@author A0130475L
#pragma once
#include "ViewType.h"


class ViewType1 : public ViewType {
private:
    static const string MESSAGE_TIMING_SEPERATOR;
    static const string MESSAGE_DISPLAY_HEADER[];
    static const string MESSAGE_NEXT;
    static const string MESSAGE_AM;
    static const string MESSAGE_PM;
    static const int TIME_STRING_INT;
    static const int TIME_MIDDAY;

    //overiding functions
    bool isInNextCategory(Task* individualTask, int i);
    vector<string> getCategoryHeader();

public:
    ViewType1(void);
    ViewType1(list<Task*> *taskList);
    ViewType1(list<Task*> *taskList, int currentDate);
    ~ViewType1(void);

    string getDateTaskString(int date);
    string getTimeTaskString(int time);
};

