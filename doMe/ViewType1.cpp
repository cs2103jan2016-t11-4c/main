#include "ViewType1.h"
const string ViewType1::MESSAGE_DISPLAY_HEADER = "Today's date is %s";
const string ViewType1::MESSAGE_NEW_LINE = "\n";
const string ViewType1::MESSAGE_AM = " am";
const string ViewType1::MESSAGE_PM = " pm";
const int ViewType1::TIME_MIDDAY = 1200;
const string ViewType1::MESSAGE_BOX = "======================================================================";
const int ViewType1::BOX_LENGTH = 21; 


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

vector<string> ViewType1::createDisplayBox(vector<string> displayList) {
    vector<string>::iterator displayListIter;

    displayList.insert(displayList.begin(),MESSAGE_BOX);
    displayList.insert(displayList.begin(),MESSAGE_VOID_STRING);
    displayListIter = displayList.begin();
    displayListIter++;

    while(displayList.size() != BOX_LENGTH) {
        displayList.push_back("");
    }

    displayList.insert(displayList.end(),MESSAGE_BOX);
    return displayList;
}

vector<string> ViewType1::createDisplayList() {
    if((*_taskList).empty()) {
        _displayList.push_back(MESSAGE_EMPTY_LIST);
    } else {
        list<Task*>::iterator taskListIter = ((*_taskList).begin());
        string complimentaryString;
        int index = 1;

        while(taskListIter != (*_taskList).end()) {

            complimentaryString = getComplimentaryString(*taskListIter);
            if(complimentaryString != MESSAGE_VOID_STRING) {
                _displayList.push_back(complimentaryString);
            }        
            _displayList.push_back(ViewType::createTaskString(*taskListIter,index));

            index++;
            taskListIter++;
        }
    }
    _displayList = createDisplayBox(_displayList);
    return _displayList;
}

