//@@author A0130475L
#pragma once
#include "ViewType.h"

class ViewType3 : public ViewType {
private:
    //overwriting funciton
    bool isInNextCategory(Task* individualTask, int i);
    vector<string> getCategoryHeader();

    static const string MESSAGE_DISPLAY_HEADER[];
    
public:
    ViewType3(void);
    ViewType3(list<Task*> *taskList, int currentDate);
    ~ViewType3(void);
};

