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

#include "Logic.h"
#include "Memory.h"
#include "CommandFeedback.h"
#include "Command.h"
#include "Task.h"
#include "ViewType.h"
#include "ViewType1.h"
#include "ViewType2.h"
#include "ViewType3.h"

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
    enum DisplayType {
        DEFAULT_DISPLAY, SEARCH_DISPLAY, HELP_DISPLAY
    };
    DisplayType _lastDisplayType;
    Logic* _logic;
    Memory* _memory;
    CommandFeedback* _commandFeedback;
    list<Task*>* _taskList;


    int _maxWindowWidth;
    int _maxWindowLength;
    char buffer[255];

    //Initial programme page
    void printProgramWelcomePage();
    void printNotificationWelcome(vector<string> welcomeStringVector);

    //prompts
    void printPromptCommand();
    void printCurrentDirectory();
    void printPromptHelp();

    //Message display
    void printMessageDisplay(Command* command);
    void printDisplayType(DisplayType display);
    void printDefaultDisplay();
    void printSearchDisplay();
    void printHelpDisplay();

    void printTaskList(int currentDate ,int viewType);
    void printSearchList(int currentDate, int viewType);
    void printHelpList(int currentDate, int viewType);

    //notification
    void printExecutionMessage(Command* executionMessage, CommandOutcome commandOutcome);

    //helper
    void showToUser(string message);
    void showToUserMessageBox();
    string getStringCommand();
    vector<string> createDisplayBox(vector<string> displayList);
    vector<string> synchronizeColourCodingWithDisplayBox(vector<string> colourCoding);
    void printList(vector<string> displayList); 
    void printList(vector<string> displayList, vector<string> colourCoding);

    //window size related function
    void setDisplayBoxLength(int size);
    
    void resizeWindow(int width, int length);
    /*
    void setWindowsRowsColumns(int size);
    int getBiggerDisplaySize(int size1, int size2);
    void synchronizeWindowsDisplaySize(int width, int length);
    */
    //window text colour
    enum Colour {
        BLACK, BLUE, GREEN, AQUA, RED, PURPLE, YELLOW, WHITE, GREY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_AQUA, LIGHT_RED, LIGHT_PURPLE, LIGHT_YELLOW, LIGHT_WHITE
    };
    static const string COLOUR_DEFAULT;
    static const string COLOUR_NEW;
    static const string COLOUR_DONE;
    static const string COLOUR_SEARCH;
    static const string COLOUR_HELP;
    static const string COLOUR_CATEGORY;
    static const string COLOUR_FEEDBACK;

    void changeListColour(string colourCoding);
    void setConsoleColor(int background, int foreground);
    void setConsoleColorDefault();

    //help scroll
    void scrollByAbsoluteCoord(int iRows);
    void keyboardCommandScroll();
	bool notExitKey(int keyPress);

    static const string SYSTEM_MODE_CON;
    static const string SYSTEM_COLOUR;
    static const string MESSAGE_WELCOME;
    static const char MESSAGE_BOX_CHARACTER;
    static const string MESSAGE_VOID_STRING; 

    static unsigned int DISPLAY_WIDTH;
    static unsigned int DISPLAY_LENGTH;
    static unsigned int DISPLAY_BOX_WIDTH;
    static unsigned int DISPLAY_BOX_LENGTH;
    static const int DISPLAY_DEFAULT_WIDTH;
    static const int DISPLAY_DEFAULT_LENGTH;
    static const int DISPLAY_SYNC_WIDTH;
    static const int DISPLAY_SYNC_LENGTH;

    static const string MESSAGE_FIRST_TIME;
    static const string MESSAGE_SAVE_FILE_NAME;
    static const string MESSAGE_SET_SAVE_FILE_DIRECTORY_PROMPT;
    static const string MESSAGE_EMPTY_SAVE_FILE_DIRECTORY;
    static const string MESSAGE_TIP_SAVE_FILE_DIRECTORY;
    static const string MESSAGE_COMMAND_PROMPT;
    static const string MESSAGE_DEFAULT_DIRECTORY;
    static const string MESSAGE_DIRECTORY_BOX;
    static const string MESSAGE_HELP_TIPS[];
};

