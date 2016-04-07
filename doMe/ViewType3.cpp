#include "ViewType3.h"

const int ViewType3::END_OF_WEEK = 6;
const string ViewType3::MESSAGE_NEW_LINE = "\n";
const string ViewType3::MESSAGE_TIMING_SEPERATOR = "-";
const string ViewType3::MESSAGE_DISPLAY_HEADER[] = {
    "-Today-",
    "-This Week-",
    "-Other Week-"
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

string ViewType3::getComplimentaryString(Task* individualTask) {
    int date;
    date = individualTask->getDate2();
    Commons commons;

    switch (_headerMarker) {
    case 0:
        _headerMarker = 1;
        if(_currentDate < date) {
            _headerMarker = 2;
        }
        return MESSAGE_DISPLAY_HEADER[0];
        break;
    case 1:
        _headerMarker = 2;
        return MESSAGE_VOID_STRING;
        //return MESSAGE_SPACE_STRING;
    case 2:
        if(_currentDate < date) {
            _headerMarker = 3;
            return MESSAGE_SPACE_STRING;
            break;
        }
        return MESSAGE_VOID_STRING;
        break;
    case 3:
        _headerMarker = 4;
        if(commons.addToDate(_dayToEndOfWeek,_currentDate) < date) {
            _headerMarker = 5;
        }
        return MESSAGE_DISPLAY_HEADER[1]; 
        break;
    case 4:
        _headerMarker = 5;
        return MESSAGE_VOID_STRING;
        //return MESSAGE_SPACE_STRING;
    case 5:
        if(commons.addToDate(_dayToEndOfWeek,_currentDate) < date) {
            _headerMarker = 6;
            return MESSAGE_SPACE_STRING;
            break;
        }
        return MESSAGE_VOID_STRING;
        break;
    case 6:
        _headerMarker = 7;
        return MESSAGE_DISPLAY_HEADER[2]; 
        break;
    default:
        return MESSAGE_VOID_STRING;
    }


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

    if(date <= weekRange && date != -1) {
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