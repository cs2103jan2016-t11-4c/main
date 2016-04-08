//@@author A0130475L
#include "ViewType3.h"

const int ViewType3::END_OF_WEEK = 6;
const string ViewType3::MESSAGE_NEW_LINE = "\n";
const string ViewType3::MESSAGE_TIMING_SEPERATOR = "-";
const string ViewType3::MESSAGE_DISPLAY_HEADER[] = {
    "<Past>",
    "<Today>",
    "<This Week>",
	"<Future>"
};

ViewType3::ViewType3(void) {
}

ViewType3::ViewType3(list<Task*> *taskList) {
    _taskList = taskList;
    _currentDate = 0;
    _headerMarker = 0;
}

ViewType3::ViewType3(list<Task*> *taskList, int currentDate) : ViewType(taskList,currentDate) {
    Commons commons;
    _headerMarker = 0;
    _dayToEndOfWeek = END_OF_WEEK - commons.getDayNumber(_currentDate);
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
        if(date >= _currentDate) {
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
    default:
        return false;
        break;
    }
    return false;
}

/****************************************************************/

string ViewType3::getTimeTaskString(int time) {
    ViewType1 view;
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
        return commons.getDateStringDay(commons.getDayNumber(date));
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
    ViewType2 view;
    return view.getMonth(date);
}
