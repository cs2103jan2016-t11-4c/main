#pragma once
#include "ViewType.h"


class ViewType1 : public ViewType {
private:
    int _headerMarker;

    static const string MESSAGE_DISPLAY_HEADER;
    static const string MESSAGE_NEW_LINE;
    static const string MESSAGE_AM;
    static const string MESSAGE_PM;

    string createTaskString(Task* individualTask, int index); 
    string getComplimentaryString(Task* individualTask);
    string getTimeTaskString(int time);

public:
    ViewType1(void);
    ViewType1(list<Task*> *taskList);
    ViewType1(list<Task*> *taskList, int currentDate);
    ~ViewType1(void);

};

