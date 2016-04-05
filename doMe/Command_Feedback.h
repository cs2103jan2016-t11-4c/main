#pragma once
#include <string>

#include "Command.h"
#include "Task.h"
#include "ViewType.h"
#include "ViewType1.h"
#include "ViewType2.h"

using namespace std;

enum CommandOutcome {
    VALID_MESSAGE, INVALID_MESSAGE
};


class Command_Feedback {
public:
    ~Command_Feedback(void);
    static Command_Feedback* getInstance();
    string getCommandFeedback(Command* executionMessage, CommandOutcome commandOutcome, int viewType);
#ifndef TESTMODE 
private: 
#else 
public: 
#endif
    static Command_Feedback* _instance;
    char buffer[255];
    Command_Feedback(void);

    string getTaskString(Task* task, int viewType); 

    //get string for individual commands
    string getNotificationUndo(Command* executionMessage, CommandOutcome commandOutcome, int viewType);
    string getNotificationRedo(Command* executionMessage, CommandOutcome commandOutcome, int viewType);

    string getNotificationAdd(Command* executionMessage, CommandOutcome commandOutcome, int viewType);
    string getNotificationDelete(Command* executionMessage, CommandOutcome commandOutcome, int viewType);
    string getNotificationEdit(Command* executionMessage, CommandOutcome commandOutcome, int viewType);
    string getNotificationClear(Command* executionMessage, CommandOutcome commandOutcome, int viewType);
    string getNotificationSearchTerm(Command* executionMessage, CommandOutcome commandOutcome, int viewType);
    string getNotificationEndSearch(Command* executionMessage, CommandOutcome commandOutcome, int viewType);
    string getNotificationViewType(Command* executionMessage, CommandOutcome commandOutcome, int viewType);
    string getNotificationChangeSaveFileDirectory(Command* executionMessage, CommandOutcome commandOutcome, int viewType);
    string getNotificationHelpPrompt(Command* executionMessage, CommandOutcome commandOutcome, int viewType);
    string getNotificationInvalidCommand(Command* executionMessage, CommandOutcome commandOutcome, int viewType);

    //valid notification
    string validNotificationAdd(Task* task, int viewType, string textFileName); 
    string validNotificationDelete(Task* task, int viewType, string textFileName);
    string validNotificationEdit(Task* task, int viewType);
    string validNotificationClear(string textFileName);
    string validNotificationSearchTerm(string searchTerm);
    string validNotificationExitSearch(); 
    string validNotificationViewType(int newViewType);
    string validNotificationChangeSaveFileDirectory(string newDirectory);
    string validNotificationHelpPrompt();

    //Invalid notification
    string invalidNotificationCommand();
    string invalidNotificationAdd();
    string invalidNotificationEdit(); 
    string invalidNotificationDelete();
    string invalidNotificationViewtype();
    string invalidNotificationSaveFileDirectory();
    string invalidNotificationUndo();

    //undo notification
    string undoNotificationAdd(Command* executionMessage, int viewType);
    string undoNotificationDel(Command* executionMessage, int viewType);
    string undoNotificationEdit(Command* executionMessage, int viewType);
    string undoNotificationClear(Command* executionMessage, int viewType);
    string undoNotificationViewType(Command* executionMessage, int viewType);
    string undoNotificationChangDirectory(Command* executionMessage, int viewType);

    static const string DEFAULT_TEXT_FILE_NAME;
    static const string MESSAGE_VOID_STRING;

    static const string MESSAGE_ADD;
    //static const string MESSAGE_EMPTY;
    static const string MESSAGE_DELETE;
    static const string MESSAGE_EDIT;
    static const string MESSAGE_CLEAR;
    static const string MESSAGE_SEARCH;
    //static const string MESSAGE_CLEAR_SEARCH;
    static const string MESSAGE_EXIT_SEARCH;
    static const string MESSAGE_VIEW_TYPE;
    static const string MESSAGE_CHANGE_FILE_DIRECTORY;
    static const string MESSAGE_HELP;
    static const string MESSAGE_REDO;

    static const string ERROR_INVALID_ADD;
    static const string ERROR_INVALID_DELETE;
    static const string ERROR_INVALID_COMMAND_FORMAT;
    static const string ERROR_INVALID_COMMAND;
    static const string ERROR_INVALID_VIEWTYPE;
    static const string ERROR_INVALID_EDIT;
    static const string ERROR_INVALID_UNDO;
    static const string ERROR_INVALID_SAVE_FILE_DIRECTORY;

    static const string MESSAGE_UNDO_COMMAND;
    static const string MESSAGE_UNDO_ADD;
    static const string MESSAGE_UNDO_DELETE;
    static const string MESSAGE_UNDO_EDIT;
    static const string MESSAGE_UNDO_CLEAR;
    static const string MESSAGE_UNDO_VIEW_TYPE;
    static const string MESSAGE_UNDO_CHANGE_DIRECTORY;
};

