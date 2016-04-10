//@@author A0130475L
#pragma once
#include <string>

using namespace std;

class Exception_CommandScroll {
private:
    static const string SCROLL_MESSAGES;
public:
    Exception_CommandScroll(void);
    ~Exception_CommandScroll(void);
    string getString();
};



