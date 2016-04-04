#pragma once
#include "ViewType.h"
#include "ViewType1.h"
#include "Commons.h"

class ViewType3 : public ViewType {
private:
    int _headerMarker;

    string getComplimentaryString(Task* individualTask);

    static const string MESSAGE_NEW_LINE;
    static const string MESSAGE_DISPLAY_HEADER[];
public:
    ViewType3(void);
    ViewType3(list<Task*> *taskList);
    ViewType3(list<Task*> *taskList, int currentDate);
    ~ViewType3(void);

    string getTimeTaskString(int time);
};

