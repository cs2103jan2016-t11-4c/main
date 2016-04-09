//@@author A0130475L
#include "ViewType1.h"

const string ViewType1::MESSAGE_TIMING_SEPERATOR = "/";
const string ViewType1::MESSAGE_NEXT = "Next ";
const string ViewType1::MESSAGE_AM = "am";
const string ViewType1::MESSAGE_PM = "pm";
const int ViewType1::TIME_STRING_INT = 4;//Meridiem size (am/pm) + 2
const int ViewType1::TIME_MIDDAY = 1200;

const string ViewType1::MESSAGE_DISPLAY_HEADER[] = {
    "<Done>",
    "<No Deadlines>",
    "<Past>",
    "<TODAY>",
    "<This Week>",
    "<Next Week>",
    "<Future>"
};

ViewType1::ViewType1(void) {
}

ViewType1::ViewType1(list<Task*> *taskList) {
    _taskList = taskList;
    _currentDate = 0;
}

ViewType1::ViewType1(list<Task*> *taskList, int currentDate) : ViewType(taskList,currentDate) {
}

ViewType1::~ViewType1(void) {
}

/****************************************************************/

string ViewType1::getTimeTaskString(int time) {
    string timeString;

    if(time >= 0) {
        if(time > TIME_MIDDAY) {
            time = time - TIME_MIDDAY;
            timeString = integerToString(time);
            timeString = timeString + MESSAGE_PM;
        } else {
            if(time < 100) {
                time = time + TIME_MIDDAY;
            } 

            timeString = integerToString(time);
            timeString = timeString + MESSAGE_AM;
        }
        timeString.insert(timeString.size() - TIME_STRING_INT, MESSAGE_TIME_SEPERATOR);
        return timeString;

    } else {
        return MESSAGE_VOID_STRING;
    }
}

vector<string> ViewType1::getCategoryHeader() {
    size_t size = (sizeof(MESSAGE_DISPLAY_HEADER)/sizeof(*MESSAGE_DISPLAY_HEADER));
    vector<string> categoryHeader(MESSAGE_DISPLAY_HEADER, MESSAGE_DISPLAY_HEADER+size);

    return categoryHeader;
}

bool ViewType1::isInNextCategory(Task* individualTask, int i) {
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
}

string ViewType1::getDateTaskString(int date) {
    string dateString;
    string day;
    string month;
    string year;
    int weekRange;
    Commons commons;

    weekRange = commons.addToDate(_dayToEndOfWeek, _currentDate);

    if(_currentDate <= date && date <= weekRange && date > 0) {
        if(_currentDate == date) {
            return MESSAGE_TODAY;
        } else {
            return commons.getDateStringDay(commons.getDayNumber(date));
        }
    } else {
        if(date > 0) {
            if(date <= weekRange + NO_OF_DAYS_IN_WEEK) {
                return MESSAGE_NEXT + commons.getDateStringDay(commons.getDayNumber(date));
            } else {
                day = getDay(date);
                month = getMonth(date);
                dateString = day + MESSAGE_TIMING_SEPERATOR + month;

                return dateString;
            }
        } else {
            return MESSAGE_VOID_STRING;
        }
    }
}


