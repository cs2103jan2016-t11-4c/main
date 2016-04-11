//@@author A0130475L
#include "ViewType1.h"

const string ViewType1::MESSAGE_DISPLAY_HEADER[] = {
    "<No Deadlines>",
    "<Past>",
    "<TODAY>",
    "<This Week>",
    "<Next Week>",
    "<Future>",
    "<Done>"
};

ViewType1::ViewType1(void) {
}

ViewType1::ViewType1(list<Task*> *taskList, int currentDate) : ViewType(taskList,currentDate) {
}

ViewType1::~ViewType1(void) {
}

/****************************************************************/

vector<string> ViewType1::getCategoryHeader() {
    size_t size = (sizeof(MESSAGE_DISPLAY_HEADER)/sizeof(*MESSAGE_DISPLAY_HEADER));
    vector<string> categoryHeader(MESSAGE_DISPLAY_HEADER, MESSAGE_DISPLAY_HEADER+size);

    return categoryHeader;
}

bool ViewType1::isInNextCategory(Task* individualTask, int i) {
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
        if(date >= 0) {
            return true;
            break;
        } else {
            return false;
            break;
        }
    case 2:
        if(date >= _currentDate) {
            return true;
            break;
        } else {
            return false;
            break;
        }
    case 3:
        if(date > _currentDate) {
            return true;
            break;
        } else {
            return false;
            break;
        }
    case 4:
        if(date > commons.addToDate(_dayToEndOfWeek,_currentDate) ) {
            return true;
            break;
        } else {
            return false;
            break;
        }
    case 5:
        if(date > commons.addToDate(_dayToEndOfWeek + NO_OF_DAYS_IN_WEEK,_currentDate) ) {
            return true;
            break;
        } else {
            return false;
            break;
        }
    case 6:
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
    /*
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
    case 5:
    if(date > commons.addToDate(_dayToEndOfWeek,_currentDate) ) {
    return true;
    break;
    } else {
    return false;
    break;
    }
    case 6:
    if(date > commons.addToDate(_dayToEndOfWeek + NO_OF_DAYS_IN_WEEK,_currentDate) ) {
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
    */
}

/****************************************************************/


