#include "UserInterface.h"
const string UserInterface::DEFAULT_TEXT_FILE_NAME = "doMe.txt";
const string UserInterface::SYSTEM_MODE_CON = "mode CON: COLS=%d lines=%d";
const char UserInterface::MESSAGE_BOX_CHARACTER = '=';
const string UserInterface::MESSAGE_VOID_STRING = "";
int UserInterface::WINDOWS_WIDTH = 80;
int UserInterface::WINDOWS_LENGTH = 40; 

const string UserInterface::MESSAGE_FIRST_TIME = "This is your first time using this programme.";
const string UserInterface::MESSAGE_SAVE_FILE_NAME = "Input your save file name: ";
const string UserInterface::MESSAGE_SET_SAVE_FILE_DIRECTORY = "New save directory: %s";
const string UserInterface::MESSAGE_SET_SAVE_FILE_DIRECTORY_PROMPT = "Set your save file directory: ";
const string UserInterface::MESSAGE_EMPTY_SAVE_FILE_DIRECTORY = "Your file is save at the current directory.";
const string UserInterface::MESSAGE_TIP_SAVE_FILE_DIRECTORY = "You can change your directory later.";

const string UserInterface::MESSAGE_COMMAND_PROMPT = "command: ";
const string UserInterface::MESSAGE_WELCOME = "Welcome to doMe. Your programme is ready for use.";
const string UserInterface::MESSAGE_ADD = "Added \"%s\" into %s";
const string UserInterface::MESSAGE_EMPTY = "Your text file \"%s\" is currently empty.";
const string UserInterface::MESSAGE_DELETE = "Deleted \"%s\" from %s";
const string UserInterface::MESSAGE_EDIT = "Edited inputted task description to \"%s\"";
const string UserInterface::MESSAGE_CLEAR = "All contents cleared from %s";
const string UserInterface::MESSAGE_SEARCH = "~Showing all results for \"%s\". Type \"exit\" to exit the search module~";
const string UserInterface::MESSAGE_CLEAR_SEARCH = "All task with the search term \"%s\" is cleared.";
const string UserInterface::MESSAGE_VIEW_TYPE = "Your current default view type is changed to (%s).";
const string UserInterface::MESSAGE_EXIT_SEARCH = "Exited search module.";
const string UserInterface::MESSAGE_UNDO_COMMAND = "Undo previous command.";

const string UserInterface::ERROR_INVALID_ADD = "Invalid addition has been inputted.";
const string UserInterface::ERROR_INVALID_DELETE = "Invalid deletion has been inputted.";
const string UserInterface::ERROR_INVALID_COMMAND_FORMAT = "Invalid command format has been inputted.";
const string UserInterface::ERROR_INVALID_COMMAND = "Invalid command has been inputted.";
const string UserInterface::ERROR_INVALID_VIEWTYPE = "Invalid viewtype has been inputted.";
const string UserInterface::ERROR_INVALID_EDIT = "Invalid editing of task description.";
const string UserInterface::ERROR_INVALID_UNDO = "Unable to undo previous command.";
const string UserInterface::ERROR_SET_INVALID_SAVE_FILE_DIRECTORY = "Invalid inputted file directory.";


const string UserInterface::MESSAGE_HELP_TIPS[] = { 
    "add <task description>", 
    "delete <index>",
    "clear",
    "edit <task description>",
    "search <keyword>",
    "change <directory>",
    "undo",
    "exit"
}; 

/*
UserInterface::UserInterface(void) {
}
*/
UserInterface::UserInterface(list<Task*> *taskList) {
    _taskList = taskList;
}

UserInterface::~UserInterface(void) {
}

/****************************************************************/

void UserInterface::printPromptFirstTimeUser() {
    showToUser(MESSAGE_FIRST_TIME);
    cout << MESSAGE_SAVE_FILE_NAME;
}

void UserInterface::printPromptFirstTimeUserDirectory() {
    cout << MESSAGE_SET_SAVE_FILE_DIRECTORY_PROMPT;
}

void UserInterface::printPromptCommand() {
    showToUserMessageBox();
    cout << MESSAGE_COMMAND_PROMPT;
}

void UserInterface::printPromptHelp() {
    size_t size = (sizeof(MESSAGE_HELP_TIPS)/sizeof(*MESSAGE_HELP_TIPS));
    vector<string> helpList(MESSAGE_HELP_TIPS,MESSAGE_HELP_TIPS+size);
    vector<string>::iterator helpListIter = helpList.begin();

    while(helpListIter!= helpList.end()) {
        showToUser(*helpListIter);
        helpListIter++;
    }
}


/****************************************************************/

void UserInterface::printNotificationWelcome() {
    showToUser(MESSAGE_WELCOME);
}

void UserInterface::printNotificationAdd(Task* task, int viewType, string textFileName) {
    string taskString;
    taskString = getTaskString(task,viewType);
    sprintf_s(buffer, MESSAGE_ADD.c_str(),taskString.c_str(), textFileName.c_str());
    showToUser(buffer);
}

void UserInterface::printNotificationDelete(Task* task, int viewType, string textFileName) {
    string taskString;
    taskString = getTaskString(task,viewType);
    sprintf_s(buffer, MESSAGE_DELETE.c_str(),taskString.c_str(), textFileName.c_str());
    showToUser(buffer);
}

void UserInterface::printNotificationEdit(Task* task, int viewType) {
    string taskString;
    taskString = getTaskString(task,viewType);
    sprintf_s(buffer, MESSAGE_EDIT.c_str(),taskString.c_str());
    showToUser(buffer);
}

void UserInterface::printNotificationClear(string textFileName) {
    sprintf_s(buffer, MESSAGE_CLEAR.c_str(), textFileName.c_str());
    showToUser(buffer);
}

void UserInterface::printNotificationEmpty(string textFileName) {
    sprintf_s(buffer, MESSAGE_EMPTY.c_str(), textFileName.c_str());
    showToUser(buffer);
}

void UserInterface::printNotificationViewTypeChange(int newViewType) {
    sprintf_s(buffer, MESSAGE_VIEW_TYPE.c_str(), newViewType);
    showToUser(buffer);
}

void UserInterface::printNotificationClearSearch(string searchTerm) {
    sprintf_s(buffer, MESSAGE_CLEAR_SEARCH.c_str(), searchTerm.c_str());
    showToUser(buffer);
}

void UserInterface::printNotificationExitSearch() {
    sprintf_s(buffer, MESSAGE_EXIT_SEARCH.c_str());
    showToUser(buffer);
}

void UserInterface::printNotificationUndo() {
    showToUser(MESSAGE_UNDO_COMMAND);
}
/****************************************************************/

void UserInterface::printNotificationInvalidAdd() {
    showToUser(ERROR_INVALID_ADD);
}

void UserInterface::printNotificationInvalidDeletion() {
    showToUser(ERROR_INVALID_DELETE);
}

void UserInterface::printNotificationInvalidCommand() {
    showToUser(ERROR_INVALID_COMMAND);
}

void UserInterface::printNotificationInvalidViewtype() {
    showToUser(ERROR_INVALID_VIEWTYPE);
}

void UserInterface::printNotificationInvalidUndo() {
    showToUser(ERROR_INVALID_UNDO);
}

void UserInterface::printNotificationInvalidEdit() {
    showToUser(ERROR_INVALID_EDIT);
}

/****************************************************************/

void UserInterface::printNotificationInvalidSaveFileDirectory() {
    showToUser(ERROR_SET_INVALID_SAVE_FILE_DIRECTORY);
}

void UserInterface::printNotificationChangeSaveFileDirectory(string newDirectory) {
    sprintf_s(buffer, MESSAGE_SET_SAVE_FILE_DIRECTORY.c_str(), newDirectory.c_str());
    showToUser(buffer);
}

void UserInterface::printNotificationEmptySaveFileDirectory() {
    showToUser(MESSAGE_EMPTY_SAVE_FILE_DIRECTORY);
    showToUser(MESSAGE_TIP_SAVE_FILE_DIRECTORY);
}

/****************************************************************/

void UserInterface::printSearchList(string searchTerm, int viewType) {
    ViewType *taskListType;

    switch(viewType) {
    case -1:
        taskListType = new ViewType(_taskList);
        break;
    case 0:
        taskListType = new ViewType0(_taskList);
        break;
    default:
        break;
    }
    printDisplayList(createDisplayBox(taskListType->createDisplayList()));
    printNotificationSearchTerm(searchTerm);
    delete taskListType;
}

void UserInterface::printTaskList(int currentDate ,int viewType) {
    ViewType *taskListType;

    switch(viewType) {
    case -1:
        taskListType = new ViewType(_taskList , currentDate);
        break;
    case 0:
        taskListType = new ViewType0(_taskList , currentDate);
        break;
    case 1:
        taskListType = new ViewType1(_taskList , currentDate);
        break;
    default:
        break;
    }
    
    printDisplayList(createDisplayBox(taskListType->createDisplayList()));
    delete taskListType;
}

/****************************************************************/

string UserInterface::getTaskString(Task* task, int viewType) {
    ViewType *taskListType;

    switch(viewType) {
    case -1:
        taskListType = new ViewType();
        break;
    case 0:
        taskListType = new ViewType0();
        break;
    default:
        break;
    }

    return taskListType->getTaskString(task);
}

/****************************************************************/

void UserInterface::printDisplayList(vector<string> displayList) {
    vector<string>::iterator displayListIter = displayList.begin();

    while(displayListIter != displayList.end()) {
        showToUser(*displayListIter);
        displayListIter++;
    }
}

void UserInterface::printNotificationSearchTerm(string searchTerm) {
    sprintf_s(buffer, MESSAGE_SEARCH.c_str(), searchTerm.c_str());
    showToUser(buffer);
}

void UserInterface::showToUser(string message) {
    cout << message << endl;
}

void UserInterface::showToUserMessageBox() {
    //if(_defaultViewType == 1) {
        string messageBox;
        setWindowsRowsColumns(0);
        messageBox.assign(WINDOWS_WIDTH,MESSAGE_BOX_CHARACTER);
        messageBox.pop_back();

        showToUser(messageBox);
        /*
    } else {
        showToUser(message);
    }
    */
}

void UserInterface::setWindowsRowsColumns(int size) {
    //system("mode CON: COLS=120 lines=40");
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;
    int rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    WINDOWS_WIDTH = columns;
    WINDOWS_LENGTH = rows - 4;

    if(size > WINDOWS_LENGTH) {
    sprintf_s(buffer, SYSTEM_MODE_CON.c_str(), columns , rows+1);
    system(buffer);
    WINDOWS_LENGTH++;
    }
}

vector<string> UserInterface::createDisplayBox(vector<string> displayList) {
    vector<string>::iterator displayListIter;
    string messageBox;

    setWindowsRowsColumns(displayList.size()+2);
    messageBox.assign(WINDOWS_WIDTH,MESSAGE_BOX_CHARACTER);
    messageBox.pop_back();

    displayList.insert(displayList.begin(),messageBox);
    displayList.insert(displayList.begin(),MESSAGE_VOID_STRING);
    displayListIter = displayList.begin();
    displayListIter++;

    while(displayList.size() < WINDOWS_LENGTH) {
        displayList.push_back(MESSAGE_VOID_STRING);
    }

    displayList.insert(displayList.end(),messageBox);
    return displayList;
}