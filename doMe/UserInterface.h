#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>

#include "Task.h"
#include "ViewType.h"
#include "ViewType0.h"

using namespace std;

class UserInterface {
private:
    int _defaultViewType;
    string _textFileName;
    char buffer[255];

    void showToUser(string string); //core helper
public:
    UserInterface(void);
    UserInterface(string textFileName, int defaultViewType);
    ~UserInterface(void);

    //doing
    void printSearchList(list<Task*>* taskList, string searchTerm);//thinking on how to implement 
    void printPromptHelp();

    //prompts
    void printPromptFirstTimeUser(); //complete
    void printPromptFirstTimeUserDirectory(); //complete
    void printPromptCommand();	//complete

    //notification
    void printNotificationWelcome(); //complete
    void printNotificationAdd(Task* task); //have extra space at the back
    void printNotificationDelete(Task* task); //complete
    void printNotificationClear(); //complete
    void printNotificationViewTypeChange(int newViewType);
    void printNotificationEmpty();
    void printNotificationChangeSaveFileDirectory(string newDirectory); //complete
    void printNotificationEmptySaveFileDirectory();  //complete
    void printNotificationClearSearch(string searchTerm);

    //error
    void printNotificationInvalidCommand(); //complete
    void printNotificationInvalidAdd(); //complete
    void printNotificationInvalidDeletion(); //complete
    void printNotificationInvalidSaveFileDirectory(); //complete

    //main printing
    void printTaskList(list<Task*> *taskList, int currentDate ,int viewType);  //complete view all task not refactored
    

    //helper
    void printDisplayList(vector<string> displayList); //helper
    string getTaskString(Task* task, int viewType); 
    void printNotificationSearchTerm(string searchTerm); //helper
};

