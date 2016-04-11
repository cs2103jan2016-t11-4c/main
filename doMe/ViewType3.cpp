//@@author A0130475L
#include "ViewType3.h"

const string ViewType3::MESSAGE_DISPLAY_HEADER[] = {
    "<No Deadlines, Past>",
    "<TODAY>",
    "<Future>",
    "<Done>"
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
    int date; 
    int date1 = individualTask->getDate1();
    int date2 = individualTask->getDate2();
    Commons commons;
    if(date1 != -1) {
        date = date1;
    } else {
        date = date2;
    }

    switch(i) {
    case 0:
        return true;
        break; 
    case 1:
        if(individualTask->getDoneStatus() == false && date >= _currentDate) {
            return true;
            break;
        } else {
            return false;
            break;
        }
    case 2:
        if(date > _currentDate) {
            return true;
            break;
        } else {
            return false;
            break;
        }
    case 3:
        if(individualTask->getDoneStatus() == true) {
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