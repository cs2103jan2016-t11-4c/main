//@@author A0130475L
#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <assert.h>

#include "Chrono.h"
#include "Logic.h"
#include "Memory.h"
#include "Command_Feedback.h"
#include "Command.h"
#include "Task.h"
#include "ViewType.h"
#include "ViewType1.h"
#include "ViewType2.h"

using namespace std;

class UserInterface {

public:
    //UserInterface(void);
    UserInterface();
    ~UserInterface(void);

    void setEnvironment();
    void executeCommandUntilExit();

#ifndef TESTMODE 
private: 
#else 
public: 
#endif

    Logic* _logic;
    Memory* _memory;
    Command_Feedback* _commandFeedback;
    list<Task*>* _taskList;

    int _maxWindowWidth;
    int _maxWindowLength;
    char buffer[255];

    static const string SYSTEM_MODE_CON;
    static string MESSAGE_WELCOME;
    static const char MESSAGE_BOX_CHARACTER;
    static const string MESSAGE_VOID_STRING; 
    static int DISPLAY_WIDTH;
    static int DISPLAY_LENGTH;

    static const string MESSAGE_FIRST_TIME;
    static const string MESSAGE_SAVE_FILE_NAME;

    static const string MESSAGE_SET_SAVE_FILE_DIRECTORY_PROMPT;
    static const string MESSAGE_EMPTY_SAVE_FILE_DIRECTORY;
    static const string MESSAGE_TIP_SAVE_FILE_DIRECTORY;

    static const string MESSAGE_COMMAND_PROMPT;

    static const string MESSAGE_HELP_TIPS[];

    //in the process of changing
    void printMessageDisplay(Command* command);
    void printDefaultDisplay();

    //main printing
    void printTaskList(int currentDate ,int viewType);
    void printSearchList(string searchTerm, int viewType);

    //command
    string getStringCommand();

    //programme page
    void printProgramWelcomePage();
    void printNotificationWelcome();

    //prompts
    void printPromptCommand();	
    void printPromptHelp();

    //notification
    void printExecutionMessage(Command* executionMessage, COMMAND_OUTCOME commandOutcome);

    //helper
    void showToUser(string message);
    void showToUserMessageBox();
    void resizeWindow(int width, int length);
    void setWindowsRowsColumns(int size);
    vector<string> createDisplayBox(vector<string> displayList);
    void printDisplayList(vector<string> displayList); 

};

