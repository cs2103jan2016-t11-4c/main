#pragma once
#include "ViewType.h"


class ViewType0 : public ViewType {
private:
    int _headerMarker;

    static const string MESSAGE_DISPLAY_HEADER;
    static const string MESSAGE_NEW_LINE;
    static const string ViewType0::MESSAGE_AM;
    static const string ViewType0::MESSAGE_PM;

    string createTaskString(Task* individualTask, int index); 
    string getComplimentaryString(Task* individualTask);
    string getTimeTaskString(int time);

public:
    ViewType0(void);
    ViewType0(list<Task*> *taskList);
    ViewType0(list<Task*> *taskList, int currentDate);
    ~ViewType0(void);

};

