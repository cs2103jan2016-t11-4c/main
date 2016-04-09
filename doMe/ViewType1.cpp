//@@author A0130475L
#include "ViewType1.h"

//const string ViewType1::MESSAGE_DISPLAY_HEADER = "Today's date is %s";
const string ViewType1::MESSAGE_DISPLAY_HEADER[] = {"Today's date is %s"};
const string ViewType1::MESSAGE_NEW_LINE = "\n";
const string ViewType1::MESSAGE_AM = "am";
const string ViewType1::MESSAGE_PM = "pm";
const int ViewType1::TIME_STRING_INT = 4;//Meridiem size (am/pm) + 2
const int ViewType1::TIME_MIDDAY = 1200;


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
/*
string ViewType1::getComplimentaryString(Task* individualTask) {
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
*/
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
    vector<string> categoryHeader;
    sprintf_s(buffer, MESSAGE_DISPLAY_HEADER[0].c_str(), (getDateTaskString(_currentDate)).c_str());
    categoryHeader.push_back(buffer);

    return categoryHeader;
}

bool ViewType1::isInNextCategory(Task* individualTask, int i) {
    switch(i) {
    case 0:
        return true;
        break;
    default:
        return false;
        break;
    }
    return false;
}


