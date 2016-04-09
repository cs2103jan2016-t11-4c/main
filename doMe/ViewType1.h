//@@author A0130475L
#pragma once
#include "ViewType.h"

class ViewType1 : public ViewType {
private:
    static const string MESSAGE_DISPLAY_HEADER[];

    //overiding functions
    bool isInNextCategory(Task* individualTask, int i);
    vector<string> getCategoryHeader();

public:
    ViewType1(void);
    ViewType1(list<Task*> *taskList, int currentDate);
    ~ViewType1(void);
};

