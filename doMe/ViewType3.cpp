//@@author A0130475L
#include "ViewType3.h"

const string ViewType3::MESSAGE_DISPLAY_HEADER[] = {
    "<Done>",
    "<No Deadlines>",
    "<Past>",
    "<TODAY>",
    "<Future>"
};

ViewType3::ViewType3(void) {
}

ViewType3::ViewType3(list<Task*> *taskList, int currentDate) : ViewType(taskList,currentDate) {
}

ViewType3::~ViewType3(void) {
}

/****************************************************************/

vector<string> ViewType3::getCategoryHeader() {
    size_t size = (sizeof(MESSAGE_DISPLAY_HEADER)/sizeof(*MESSAGE_DISPLAY_HEADER));
    vector<string> categoryHeader(MESSAGE_DISPLAY_HEADER, MESSAGE_DISPLAY_HEADER+size);

    return categoryHeader;
}

bool ViewType3::isInNextCategory(Task* individualTask, int i) {
    int date = individualTask->getDate2();
    Commons commons;

    switch(i) {
    case 0:
        return true;
        break; 
    case 1:
        if(individualTask->getDoneStatus() == false) {
            return true;
            break;
        } else {
            return false;
            break;
        }
    case 2:
        if(date >= 0) {
            return true;
            break;
        } else {
            return false;
            break;
        }
    case 3:
        if(date >= _currentDate) {
            return true;
            break;
        } else {
            return false;
            break;
        }
    case 4:
        if(date > _currentDate) {
            return true;
            break;
        } else {
            return false;
            break;
        }
    default:
        return false;
        break;
    }
    return false;
}

/****************************************************************/