//@@author A0130475L
#pragma once
#include "ViewType.h"

class ViewType2 : public ViewType {
private:
    static const string MESSAGE_DISPLAY_HEADER[];

    //overiding functions
    bool isInNextCategory(Task* individualTask, int i);
    vector<string> getCategoryHeader();
   
public:
    ViewType2(void);
    ViewType2(list<Task*> *taskList, int currentDate);
    ~ViewType2(void);
};

