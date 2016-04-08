//@@author A0130475L
#pragma once
#include "ViewType.h"
#include "ViewType1.h"
#include "ViewType2.h"
#include "Commons.h"

class ViewType3 : public ViewType {
private:
    int _headerMarker;
    int _dayToEndOfWeek;

    //overwriting funciton
    bool isInNextCategory(Task* individualTask, int i);
    vector<string> getCategoryHeader();

    static const int END_OF_WEEK;
    static const string MESSAGE_NEW_LINE;
    static const string MESSAGE_TIMING_SEPERATOR;
    static const string MESSAGE_DISPLAY_HEADER[];
    
public:
    ViewType3(void);
    ViewType3(list<Task*> *taskList);
    ViewType3(list<Task*> *taskList, int currentDate);
    ~ViewType3(void);

    string getTimeTaskString(int time);
    string getDateTaskString(int date); 
    string getMonth(int date); 
};

