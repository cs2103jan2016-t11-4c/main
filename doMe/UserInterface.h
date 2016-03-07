#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <windows.h>

#include "Task.h"
#include "ViewType.h"
#include "ViewType0.h"
#include "ViewType1.h"

using namespace std;

class UserInterface {

public:
    //UserInterface(void);
    UserInterface(list<Task*> *taskList);
    ~UserInterface(void);

    //programme page
    void printProgramWelcomePage();

    //prompts
    void printPromptFirstTimeUser(); 
    void printPromptFirstTimeUserDirectory(); 
    void printPromptCommand();	

    //notification
    void printNotificationWelcome();
    void printPromptHelp();
    void printNotificationAdd(Task* task, int viewType, string textFileName);
    void printNotificationDelete(Task* task, int viewType, string textFileName);
    void printNotificationClear(string textFileName);
    void printNotificationViewTypeChange(int newViewType);
    void printNotificationEmpty(string textFileName); 
    void printNotificationChangeSaveFileDirectory(string newDirectory);
    void printNotificationEmptySaveFileDirectory();
    void printNotificationSearchTerm(string searchTerm);
    void printNotificationClearSearch(string searchTerm);
    void printNotificationExitSearch(); //............................................new//
    void printNotificationUndo(); //............................................new//
    void printNotificationEdit(Task* task, int viewType); //......................new//

    //error
    void printNotificationInvalidCommand();
    void printNotificationInvalidAdd();
    void printNotificationInvalidDeletion();
    void printNotificationInvalidSaveFileDirectory();
    void printNotificationInvalidViewtype(); //............................................new//
    void printNotificationInvalidUndo(); //............................................new//
    void printNotificationInvalidEdit();  //............................................new//

    //main printing
    void printTaskList(int currentDate ,int viewType);
    void printSearchList(string searchTerm, int viewType);

#ifndef TESTMODE 
private: 
#else 
public: 
#endif

    list<Task*> *_taskList;
    int _maxWindowWidth;
    int _maxWindowLength;
    char buffer[255];

    static const string DEFAULT_TEXT_FILE_NAME;
    static const string SYSTEM_MODE_CON;
    static const char MESSAGE_BOX_CHARACTER;
    static const string MESSAGE_VOID_STRING; 
    static int WINDOWS_WIDTH;
    static int WINDOWS_LENGTH;

    static const string MESSAGE_FIRST_TIME;
    static const string MESSAGE_SAVE_FILE_NAME;
    static const string MESSAGE_SET_SAVE_FILE_DIRECTORY;
    static const string MESSAGE_SET_SAVE_FILE_DIRECTORY_PROMPT;
    static const string MESSAGE_EMPTY_SAVE_FILE_DIRECTORY;
    static const string MESSAGE_TIP_SAVE_FILE_DIRECTORY;

    static const string MESSAGE_COMMAND_PROMPT;
    static const string MESSAGE_WELCOME;
    static const string MESSAGE_ADD;
    static const string MESSAGE_EMPTY;
    static const string MESSAGE_DELETE;
    static const string MESSAGE_EDIT;
    static const string MESSAGE_CLEAR;
    static const string MESSAGE_SEARCH;
    static const string MESSAGE_CLEAR_SEARCH;
    static const string MESSAGE_EXIT_SEARCH;
    static const string MESSAGE_VIEW_TYPE;
    static const string MESSAGE_UNDO_COMMAND;

    static const string ERROR_INVALID_ADD;
    static const string ERROR_INVALID_DELETE;
    static const string ERROR_INVALID_COMMAND_FORMAT;
    static const string ERROR_INVALID_COMMAND;
    static const string ERROR_INVALID_VIEWTYPE;
    static const string ERROR_INVALID_EDIT;
    static const string ERROR_INVALID_UNDO;
    static const string ERROR_SET_INVALID_SAVE_FILE_DIRECTORY;

    static const string MESSAGE_HELP_TIPS[];

    //helper
    void showToUser(string message);
    void showToUserMessageBox();
    void setWindowsRowsColumns(int size);
    vector<string> createDisplayBox(vector<string> displayList);
    void printDisplayList(vector<string> displayList); 
    string getTaskString(Task* task, int viewType); //incomplete

};

