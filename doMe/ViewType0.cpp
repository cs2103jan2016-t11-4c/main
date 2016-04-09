#include "ViewType0.h"

ViewType0::ViewType0(void) {
}

ViewType0::~ViewType0(void) {
}

ViewType0::ViewType0(list<Task*> *taskList, int currentDate) : ViewType(taskList, currentDate) {
}

/****************************************************************/

string ViewType0::getDateTaskString(int date) {
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

string ViewType0::getTimeTaskString(int time) {
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

string ViewType0::getMonth(int date) {
    ostringstream oss;
    date = date / 100;
    oss << date % 100;
    return oss.str();
}
