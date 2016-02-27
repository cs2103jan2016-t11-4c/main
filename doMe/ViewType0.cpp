#include "ViewType0.h"
const string ViewType0::MESSAGE_DISPLAY_HEADER = "Today's date is %s. \n";
const string ViewType0::MESSAGE_NEW_LINE = "\n";

ViewType0::ViewType0(void) {
}

ViewType0::ViewType0(list<Task*> *taskList, int currentDate) : ViewType(taskList,currentDate) {
    _headerMarker = 0;
}

ViewType0::ViewType0(list<Task*> *taskList, int currentDate, int headerMarker) : ViewType(taskList,currentDate) {
    _headerMarker = headerMarker; //still in planning phase
}

ViewType0::~ViewType0(void) {
}

string ViewType0::getTaskString(Task* individualTask) {
    string headerString = createHeaderString(individualTask->getDate2());

    string name = individualTask->getName();
    string location = individualTask->getLocation();
    string date1 = getDateTaskString(individualTask->getDate1());
    string date2 = getDateTaskString(individualTask->getDate2());
    string time1 = getTimeTaskString(individualTask->getTime1());
    string time2 = getTimeTaskString(individualTask->getTime2());

    string taskString = formatTaskString(name,date1,date2,time1,time2,location);

    return headerString + taskString;
}

string ViewType0::createHeaderString(int date) {
    if(date == _currentDate) {
        if(_headerMarker == 0) {
            sprintf_s(buffer, MESSAGE_DISPLAY_HEADER.c_str(), (getDateTaskString(_currentDate)).c_str());
            _headerMarker = 1;
            return buffer;
        }
    } else {
        if(_headerMarker == 1) {
            _headerMarker = 2;
            return MESSAGE_NEW_LINE;
        } 
    }
    return MESSAGE_VOID_STRING;
}


