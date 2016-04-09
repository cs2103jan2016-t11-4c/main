//@@author A0130475L
#include "ViewType3.h"

const string ViewType3::MESSAGE_TIMING_SEPERATOR = "-";
const string ViewType3::MESSAGE_DISPLAY_HEADER[] = {
    "<Done>",
    "<No Deadlines>",
    "<Past>",
    "<TODAY>",
    "<Future>"
};

ViewType3::ViewType3(void) {
}

ViewType3::ViewType3(list<Task*> *taskList) {
    _taskList = taskList;
    _currentDate = 0;
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

string ViewType3::getTimeTaskString(int time) {
    ViewType1 view(_taskList, _currentDate);
    return view.getTimeTaskString(time);
}

string ViewType3::getDateTaskString(int date) {
    string dateString;
    string day;
    string month;
    string year;
    int weekRange;
    Commons commons;

    weekRange = commons.addToDate(_dayToEndOfWeek, _currentDate);

    if(_currentDate <= date && date <= weekRange && date != -1) {
        if(_currentDate == date) {
            return MESSAGE_TODAY;
        } else {
            return commons.getDateStringDay(commons.getDayNumber(date));
        }
    } else {
        if(date > 0) {
            day = getDay(date);
            month = getMonth(date);
            dateString = day + MESSAGE_TIMING_SEPERATOR + month;

            return dateString;
        } else {
            return MESSAGE_VOID_STRING;
        }
    }
}

string ViewType3::getMonth(int date) {
    ViewType2 view(_taskList, _currentDate);
    return view.getMonth(date);
}
