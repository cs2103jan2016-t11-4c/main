#pragma once
#include "ViewType.h"

using namespace std;

class ViewType0 : public ViewType {
private:
    string getDateTaskString(int date);
    string getTimeTaskString(int time);
    string getMonth(int date);

public:
    ViewType0(void);
    ViewType0::ViewType0(list<Task*> *taskList, int currentDate);
    ~ViewType0(void);
};

