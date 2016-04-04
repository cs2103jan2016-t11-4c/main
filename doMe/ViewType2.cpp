//@@author A0130475L
#include "ViewType2.h"

const string ViewType2::MESSAGE_DISPLAY_HEADER = "Today's date is %s";
const string ViewType2::MESSAGE_NEW_LINE = "\n";
const string ViewType2::MESSAGE_AM = "am";
const string ViewType2::MESSAGE_PM = "pm";
const string ViewType2::MESSAGE_TIMING_SEPERATOR = "-";
const int ViewType2::TIME_STRING_INT = 4;//Meridiem size (am/pm) + 2
const int ViewType2::TIME_MIDDAY = 1200;
const string ViewType2::MESSAGE_BOX = "======================================================================";
const string ViewType2::MESSAGE_MONTH[] = { 
    "Jan", 
    "Feb",
    "Mar",
    "Apr",
    "May",
    "Jun",
    "Jul",
    "Aug",
    "Sep",
    "Oct",
    "Nov",
    "Dec"
}; 



ViewType2::ViewType2(void) {
}

ViewType2::ViewType2(list<Task*> *taskList) {
    _taskList = taskList;
    _currentDate = 0;
    _headerMarker = 0;
}

ViewType2::ViewType2(list<Task*> *taskList, int currentDate) : ViewType(taskList,currentDate) {
    _headerMarker = 0;
}

ViewType2::~ViewType2(void) {
}

/****************************************************************/

string ViewType2::getComplimentaryString(Task* individualTask) {
    int date;
    date = individualTask->getDate2();

    switch (_headerMarker) {
    case 0:
        sprintf_s(buffer, MESSAGE_DISPLAY_HEADER.c_str(), (getDateTaskString(_currentDate)).c_str());
        _headerMarker = 1;
        if(_currentDate < date) {
            _headerMarker = 2;
             return buffer + MESSAGE_NEW_LINE;
        } else {
        return buffer;
        break;
    }
    case 1:
        if(_currentDate < date) {    
            _headerMarker = 2;
            return MESSAGE_SPACE_STRING;
            break;
        } 
        break;
    }
    return MESSAGE_VOID_STRING;
}

/****************************************************************/

string ViewType2::getTimeTaskString(int time) {
    ViewType1 view;
    return view.getTimeTaskString(time);
}

string ViewType2::getDateTaskString(int date) {
    string dateString;
    string day;
    string month;
    string year;

    if(date > 0) {
        day = getDay(date);
        month = getMonth(date);
        //year = getYear(date);
        dateString = day + MESSAGE_TIMING_SEPERATOR + month;

        return dateString;
    } else {
        return MESSAGE_VOID_STRING;
    }
}

string ViewType2::getMonth(int date) {
    int month;
    date = date / 100;
    month = date % 100;
    assert((month <= 12) && (month > 0));

    return MESSAGE_MONTH[month-1];
}

