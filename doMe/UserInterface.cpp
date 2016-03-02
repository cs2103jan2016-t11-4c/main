#include "UserInterface.h"
const string UserInterface::DEFAULT_TEXT_FILE_NAME = "doMe.txt";

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
const string UserInterface::MESSAGE_CLEAR = "All contents cleared from %s";
const string UserInterface::MESSAGE_SEARCH = "~Showing result for \"%s\". Type \"exit\" to exit the search module~";
const string UserInterface::MESSAGE_CLEAR_SEARCH = "All task with the search term \"%s\" is cleared.";
const string UserInterface::MESSAGE_VIEW_TYPE = "Your current default view type is changed to (%s).";

const string UserInterface::ERROR_INVALID_ADD = "Invalid addition has been inputted.";
const string UserInterface::ERROR_INVALID_DELETE = "Invalid deletion has been inputted.";
const string UserInterface::ERROR_INVALID_COMMAND_FORMAT = "Invalid command format has been inputted.";
const string UserInterface::ERROR_INVALID_COMMAND = "Invalid command has been inputted.";
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

UserInterface::UserInterface(void) {
    _textFileName = DEFAULT_TEXT_FILE_NAME;
    _defaultViewType = -1;
}

UserInterface::UserInterface(string textFileName, int defaultViewType) {
    _textFileName = textFileName;
    _defaultViewType = defaultViewType;
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

void UserInterface::printNotificationAdd(Task* task) {
    string taskString;
    taskString = getTaskString(task,_defaultViewType);
    sprintf_s(buffer, MESSAGE_ADD.c_str(),taskString.c_str(), _textFileName.c_str());
    showToUser(buffer);
}

void UserInterface::printNotificationDelete(Task* task) {
    string taskString;
    taskString = getTaskString(task,_defaultViewType);
    sprintf_s(buffer, MESSAGE_DELETE.c_str(),taskString.c_str(), _textFileName.c_str());
    showToUser(buffer);
}

void UserInterface::printNotificationClear() {
    sprintf_s(buffer, MESSAGE_CLEAR.c_str(), _textFileName.c_str());
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

void UserInterface::printNotificationEmpty() {
    sprintf_s(buffer, MESSAGE_EMPTY.c_str(), _textFileName.c_str());
    showToUser(buffer);
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

void UserInterface::printSearchList(list<Task*>* taskList, string searchTerm) {
    printNotificationSearchTerm(searchTerm);
    ViewType *taskListType;

    switch(_defaultViewType) {
    case -1:
        taskListType = new ViewType(taskList);
        break;
    case 0:
        taskListType = new ViewType0(taskList);
        break;
    default:
        break;
    }
    printDisplayList(taskListType->createSearchList());
    delete taskListType;

}

void UserInterface::printTaskList(list<Task*> *taskList, int currentDate ,int viewType) {
    ViewType *taskListType;

    switch(viewType) {
    case -1:
        taskListType = new ViewType(taskList , currentDate);
        break;
    case 0:
        taskListType = new ViewType0(taskList , currentDate);
        break;
    default:
        break;
    }
    printDisplayList(taskListType->createDisplayList());
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

void UserInterface::showToUser(string string) {
    cout << string << endl;
}