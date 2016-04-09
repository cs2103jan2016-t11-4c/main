//@@author A0130475L
#include "ViewType.h"

const int ViewType::END_OF_WEEK = 6;
const int ViewType::NO_OF_DAYS_IN_WEEK = 7;
const string ViewType::MESSAGE_TODAY = "Today";
const string ViewType::MESSAGE_DISPLAY_CONTENTS = "%d. %s";
const string ViewType::MESSAGE_DATE_SEPERATOR = "/";
const string ViewType::MESSAGE_TIME_SEPERATOR = ":";
const string ViewType::MESSAGE_TIMING_SEPERATOR = "- ";
const string ViewType::MESSAGE_VOID_STRING = "";
const string ViewType::MESSAGE_SPACE_STRING = " ";
const string ViewType::MESSAGE_BRACKETS = "(%s)";
const string ViewType::MESSAGE_FLOATING_TASK = "<No deadline>";
const string ViewType::MESSAGE_EMPTY_LIST[] = {
    "                               <list is empty!>",
    "                 Type \"HELP\" to see list of available commands."
};
//const string ViewType::MESSAGE_DISPLAY_HEADER[] = {""};

const string ViewType::COLOUR_DEFAULT = "DEFAULT";
const string ViewType::COLOUR_NEW = "NEW";
const string ViewType::COLOUR_DONE = "DONE";
const string ViewType::COLOUR_CATEGORY = "CATEGORY";

ViewType::ViewType(void) {
}

ViewType::ViewType(list<Task*> *taskList) {
    _taskList = taskList;
    _currentDate = 0;
}

ViewType::ViewType(list<Task*> *taskList, int currentDate) {
    Commons commons;
    _taskList = taskList;
    _currentDate = currentDate;
    _dayToEndOfWeek = END_OF_WEEK - commons.getDayNumber(_currentDate);
}

ViewType::~ViewType(void) {
}

/****************************************************************/
/*
vector<string> ViewType::createDisplayList() {
if((*_taskList).empty()) {
_displayList.push_back(MESSAGE_EMPTY_LIST);
} else {
list<Task*>::iterator taskListIter = ((*_taskList).begin());
string complimentaryString;
Memory* memory;
int index = 1;

memory = Memory::getInstance();
Task* recentTask = memory->ramGetLastModifiedTask();

while(taskListIter != (*_taskList).end()) {
complimentaryString = getComplimentaryString(*taskListIter);

if(complimentaryString != MESSAGE_VOID_STRING) {
_displayList.push_back(complimentaryString);
_colourCoding.push_back(COLOUR_DEFAULT);
}

if(complimentaryString != MESSAGE_SPACE_STRING) {
_colourCoding.push_back(colourCoderTag(*taskListIter, recentTask));
_displayList.push_back(createTaskString(*taskListIter,index));
index++;
taskListIter++;
}
}
}
return _displayList;
}
*/

vector<string> ViewType::createDisplayList() {
    if((*_taskList).empty()) {
        size_t size = (sizeof(MESSAGE_EMPTY_LIST)/sizeof(*MESSAGE_EMPTY_LIST));
        vector<string> emptyList(MESSAGE_EMPTY_LIST,MESSAGE_EMPTY_LIST+size);
        _displayList = emptyList;
    } else {
        list<Task*>::iterator taskListIter = ((*_taskList).begin());
        Memory* memory;
        int index = 1;
        unsigned int i = 0;

        memory = Memory::getInstance();
        Task* recentTask = memory->ramGetLastModifiedTask();

        vector<string> categoryHeader = getCategoryHeader();

        if(!categoryHeader.empty()) {
            _displayList.push_back(categoryHeader[i]);
            _colourCoding.push_back(COLOUR_CATEGORY);
            i++;
        }
        while(taskListIter != (*_taskList).end()) {
            while((isInNextCategory(*taskListIter, i)) && (i < categoryHeader.size())) {
                _displayList.push_back("");
                _colourCoding.push_back(COLOUR_DEFAULT);

                _displayList.push_back(categoryHeader[i]);
                _colourCoding.push_back(COLOUR_CATEGORY);
                i++;
            }

            _displayList.push_back(createTaskString(*taskListIter,index));
            _colourCoding.push_back(colourCoderTag(*taskListIter, recentTask));
            index++;
            taskListIter++;
        }
    }
    return _displayList;
}

vector<string> ViewType::getCategoryHeader() {
    vector<string> null;
    return null;
}

bool ViewType::isInNextCategory(Task* individualTask, int i) {
    return true;
}

string ViewType::colourCoderTag(Task* individualTask, Task* recentTask) {
    if(individualTask->getDoneStatus() == 1) {
        return COLOUR_DONE;
    } else {
        if(recentTask == individualTask) {
            return COLOUR_NEW;
        } 
        return COLOUR_DEFAULT;
    }
}

//search list without complimentary string
vector<string> ViewType::createSearchList() {
    if((*_taskList).empty()) {
        size_t size = (sizeof(MESSAGE_EMPTY_LIST)/sizeof(*MESSAGE_EMPTY_LIST));
        vector<string> emptyList(MESSAGE_EMPTY_LIST,MESSAGE_EMPTY_LIST+size);
        _displayList = emptyList;
    } else {
        list<Task*>::iterator taskListIter = (*_taskList).begin();
        int index = 1;

        while(taskListIter != (*_taskList).end()) {
            _displayList.push_back(ViewType::createTaskString(*taskListIter,index));
            index++;
            taskListIter++;
        }
    }
    return _displayList;
}

//create task string with index
string ViewType::createTaskString(Task* individualTask, int index) {
    string taskString;
    taskString = getTaskString(individualTask);

    sprintf_s(buffer, MESSAGE_DISPLAY_CONTENTS.c_str(),index, taskString.c_str());

    return buffer;
}

string ViewType::getTaskString(Task* individualTask) {
    string name = individualTask->getName();
    string location = individualTask->getLocation();
    string date1 = getDateTaskString(individualTask->getDate1());
    string date2 = getDateTaskString(individualTask->getDate2());
    string time1 = getTimeTaskString(individualTask->getTime1());
    string time2 = getTimeTaskString(individualTask->getTime2());

    string taskString = formatTaskString(name,date1,date2,time1,time2,location);

    return taskString;
}

/****************************************************************/

string ViewType::integerToString(int integer) {
    ostringstream oss;
    oss << integer;  
    return oss.str();
}

string ViewType::timeToString(string time) {
    string timeString = time;
    if(time.size() < 3) {
        timeString.insert(0,"0");
    }
    if(time.size()  < 2) {
        timeString.insert(0,"0");
    }
    return timeString;
}

/****************************************************************/
//default format of ordering: name - (location) time1 date1 - time2 date2
string ViewType::formatTaskString(string name , string date1 , string date2 , string time1 , string time2 , string location) {
    string taskString;
    string dateString;

    name = formateAddSpace(name);
    date1 = formateAddSpace(date1);
    date2 = formateAddSpace(date2);
    time1 = formateAddSpace(time1);
    time2 = formateAddSpace(time2);

    location = formateAddBracket(location);
    location = formateAddSpace(location);

    dateString = formateDateString(time1 + date1 , time2 + date2);
    taskString = name + location + dateString;

    //taskString.pop_back();
    return taskString;
}

string ViewType::formateAddSpace(string s) {
    if(!s.empty()) {
        return s + MESSAGE_SPACE_STRING;
    } 
    return s;
}

string ViewType::formateAddBracket(string s) {
    if(!s.empty()) {
        sprintf_s(buffer, MESSAGE_BRACKETS.c_str(), s.c_str());
        return buffer;
    }
    return s;
}

string ViewType::formateDateString(string s1, string s2) {
    string time;
    if((s1.empty()) && (s2.empty())) {
        return MESSAGE_FLOATING_TASK;
    }
    if((s1.empty()) || (s2.empty())) {
        time = s1 + s2;
        time.pop_back();
        sprintf_s(buffer, MESSAGE_BRACKETS.c_str(),time.c_str());
        return buffer;
    } else {
        time = s1 + MESSAGE_TIMING_SEPERATOR + s2;
        time.pop_back();
        sprintf_s(buffer, MESSAGE_BRACKETS.c_str(),time.c_str());
        return buffer;

    }
}

/****************************************************************/
/*Overriding functions*/
/****************************************************************/
//headers + additional lines to compliment to viewtype (default void)

string ViewType::getDateTaskString(int date) {
    string dateString;
    string day;
    string month;
    string year;

    if(date > 0) {
        day = getDay(date);
        month = getMonth(date);
        year = getYear(date);
        dateString = day + MESSAGE_DATE_SEPERATOR + month + MESSAGE_DATE_SEPERATOR + year;

        return dateString;
    } else {
        return MESSAGE_VOID_STRING;
    }
}

string ViewType::getTimeTaskString(int time) {
    string timeString;

    if(time >= 0) {
        timeString = integerToString(time);
        timeString = timeToString(timeString);

        timeString.insert(timeString.size() - 2,MESSAGE_TIME_SEPERATOR);

        return timeString;
    } else {
        return MESSAGE_VOID_STRING;
    }
}

vector<string> ViewType::getColourCoding() {
    return _colourCoding;
}

/****************************************************************/

string ViewType::getDay(int date) {
    ostringstream oss;
    oss << date % 100;
    return oss.str();
}

string ViewType::getMonth(int date) {
    ostringstream oss;
    date = date / 100;
    oss << date % 100;
    return oss.str();
}

string ViewType::getYear(int date) {
    ostringstream oss;
    oss << date / 10000;
    return oss.str();
}

