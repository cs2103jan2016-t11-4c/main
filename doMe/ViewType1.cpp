#include "ViewType1.h"
const string ViewType1::MESSAGE_DISPLAY_HEADER = "Today's date is %s";
const string ViewType1::MESSAGE_NEW_LINE = "\n";
const string ViewType1::MESSAGE_AM = " am";
const string ViewType1::MESSAGE_PM = " pm";
const string ViewType1::MESSAGE_TIMING_SEPERATOR = "-";
const int ViewType1::TIME_MIDDAY = 1200;
const string ViewType1::MESSAGE_BOX = "======================================================================";
const int ViewType1::BOX_LENGTH = 21; 
const string ViewType1::MESSAGE_MONTH[] = { 
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



ViewType1::ViewType1(void) {
}

ViewType1::ViewType1(list<Task*> *taskList) {
    _taskList = taskList;
    _currentDate = 0;
    _headerMarker = 0;
}

ViewType1::ViewType1(list<Task*> *taskList, int currentDate) : ViewType(taskList,currentDate) {
    _headerMarker = 0;
}

ViewType1::~ViewType1(void) {
}

/****************************************************************/

string ViewType1::getComplimentaryString(Task* individualTask) {
    int date;
    date = individualTask->getDate2();

    switch (_headerMarker) {
    case 0:
        sprintf_s(buffer, MESSAGE_DISPLAY_HEADER.c_str(), (getDateTaskString(_currentDate)).c_str());
        _headerMarker = 1;
        return buffer;
        break;
    case 1:
        if(_currentDate != date) {    
            _headerMarker = 2;
            return MESSAGE_SPACE_STRING;
            break;
        } 
        break;
    }
    return MESSAGE_VOID_STRING;
}

string ViewType1::getTimeTaskString(int time) {
    string timeString;

    if(time >= 0) {
        if(time >= TIME_MIDDAY) {
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
        timeString.insert(timeString.size() - 5, MESSAGE_TIME_SEPERATOR);
        return timeString;

    } else {
        return MESSAGE_VOID_STRING;
    }
}

/****************************************************************/

string ViewType1::getDateTaskString(int date) {
    string dateString;
    string day;
    string month;
    string year;

    if(date >= 0) {
        day = getDay(date);
        month = getMonth(date);
        //year = getYear(date);
        dateString = day + MESSAGE_TIMING_SEPERATOR + month;

        return dateString;
    } else {
        return MESSAGE_VOID_STRING;
    }
}

string ViewType1::getMonth(int date) {
    int month;
    date = date / 100;
    month = date % 100;
    return MESSAGE_MONTH[month-1];
}

