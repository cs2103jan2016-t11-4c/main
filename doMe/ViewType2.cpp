//@@author A0130475L
#include "ViewType2.h"

const string ViewType2::MESSAGE_DISPLAY_HEADER[] = {
    "<No Deadlines, Past>",
    "<TODAY>",
    "<This Week>",
    "<Next Week>",
    "<Future>",
    "<Done>"
};

ViewType2::ViewType2(void) {
}

ViewType2::ViewType2(list<Task*> *taskList, int currentDate) : ViewType(taskList,currentDate) {
}

ViewType2::~ViewType2(void) {
}

/****************************************************************/

vector<string> ViewType2::getCategoryHeader() {
    size_t size = (sizeof(MESSAGE_DISPLAY_HEADER)/sizeof(*MESSAGE_DISPLAY_HEADER));
    vector<string> categoryHeader(MESSAGE_DISPLAY_HEADER, MESSAGE_DISPLAY_HEADER+size);

    return categoryHeader;
}

bool ViewType2::isInNextCategory(Task* individualTask, int i) {
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
        if(date > commons.addToDate(_dayToEndOfWeek,_currentDate) ) {
            return true;
            break;
        } else {
            return false;
            break;
        }
    case 4:
        if(date > commons.addToDate(_dayToEndOfWeek + NO_OF_DAYS_IN_WEEK,_currentDate) ) {
            return true;
            break;
        } else {
            return false;
            break;
        }
    case 5:
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


