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

#include "Chrono.h"
#include "Logic.h"
#include "Memory.h"
#include "Command.h"
#include "Task.h"
#include "ViewType.h"
#include "ViewType1.h"
#include "ViewType2.h"

using namespace std;

enum COMMAND_OUTCOME {
    VALID_MESSAGE, INVALID_MESSAGE, UNDO_MESSAGE
};

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
    list<Task*>* _taskList;

    //int _commandOutcome;

    int _maxWindowWidth;
    int _maxWindowLength;
    char buffer[255];

    static const string DEFAULT_TEXT_FILE_NAME;
    static const string SYSTEM_MODE_CON;
    static const char MESSAGE_BOX_CHARACTER;
    static const string MESSAGE_VOID_STRING; 
    static int DISPLAY_WIDTH;
    static int DISPLAY_LENGTH;
    static const int DEFAULT_WINDOWS_WIDTH;
    static const int DEFAULT_WINDOWS_LENGTH; 

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

    //in the process of changing
    void printBeforeMessageDisplay();
    void printExecutionMessage(Command* executionMessage, COMMAND_OUTCOME commandOutcome);

    void printNotificationUndo(Command* executionMessage);
    void printNotificationAdd(Command* executionMessage, COMMAND_OUTCOME commandOutcome);
    void printNotificationDelete(Command* executionMessage, COMMAND_OUTCOME commandOutcome);
    void printNotificationEdit(Command* executionMessage, COMMAND_OUTCOME commandOutcome);
    void printNotificationClear(Command* executionMessage, COMMAND_OUTCOME commandOutcome);
    void printNotificationSearchTerm(Command* executionMessage, COMMAND_OUTCOME commandOutcome);
    void printNotificationEndSearch(Command* executionMessage, COMMAND_OUTCOME commandOutcome);
    void printNotificationViewType(Command* executionMessage, COMMAND_OUTCOME commandOutcome);
    void printNotificationChangeSaveFileDirectory(Command* executionMessage, COMMAND_OUTCOME commandOutcome);
    void printNotificationInvalidCommand(Command* executionMessage, COMMAND_OUTCOME commandOutcome);

    //command
    string getStringCommand();

    //programme page
    void setDefaultWindowsRowsColumns();
    void printProgramWelcomePage();

    //prompts
    void printPromptFirstTimeUser(); 
    void printPromptFirstTimeUserDirectory(); 
    void printPromptCommand();	

    //notification
    void printNotificationWelcome();
    void printPromptHelp();

    void validNotificationAdd(Task* task, int viewType, string textFileName); 
    void validNotificationDelete(Task* task, int viewType, string textFileName);
    void validNotificationEdit(Task* task, int viewType);
    void validNotificationClear(string textFileName);
    void validNotificationSearchTerm(string searchTerm);
    void validNotificationExitSearch(); 
    void validNotificationViewType(int newViewType);
    void validNotificationChangeSaveFileDirectory(string newDirectory);

    //additional valid notification (Havent change name)
    void printNotificationEmpty(string textFileName); 
    void printNotificationEmptySaveFileDirectory();
    void printNotificationClearSearch(string searchTerm);

    //Invalid notification
    void invalidNotificationCommand();

    void invalidNotificationAdd();
    void invalidNotificationEdit(); 
    void invalidNotificationDelete();
    void invalidNotificationViewtype();
    void invalidNotificationSaveFileDirectory();
    void invalidNotificationUndo();

    //main printing
    void printTaskList(int currentDate ,int viewType);
    void printSearchList(string searchTerm, int viewType);

    //helper
    void showToUser(string message);
    void showToUserMessageBox();
    void setWindowsRowsColumns(int size);
    vector<string> createDisplayBox(vector<string> displayList);
    void printDisplayList(vector<string> displayList); 
    string getTaskString(Task* task, int viewType); //incomplete

};

