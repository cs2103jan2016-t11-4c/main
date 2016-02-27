#include "UserInterface.h"
const string DEFAULT_TEXT_FILE_NAME = "doMe.txt";

const string MESSAGE_FIRST_TIME = "This is your first time using this programme";
const string MESSAGE_SAVE_FILE_NAME = "Input your save file name: ";
const string MESSAGE_SET_SAVE_FILE_DIRECTORY = "New save directory: %s";
const string MESSAGE_SET_SAVE_FILE_DIRECTORY_PROMPT = "Set your save file directory: ";
const string MESSAGE_EMPTY_SAVE_FILE_DIRECTORY = "Your file is save at the current directory";
const string MESSAGE_TIP_SAVE_FILE_DIRECTORY = "You can change your directory later";

const string COMMAND_PROMPT = "command: ";
const string MESSAGE_WELCOME = "Welcome to doMe. Your programme is ready for use";
const string MESSAGE_ADD = "Added \"%s\" into %s";
const string MESSAGE_EMPTY = "Your text file \"%s\" is currently empty";
const string MESSAGE_DELETE = "Deleted \"%s\" from %s";
const string MESSAGE_CLEAR = "all contents cleared from %s";
const string MESSAGE_SEARCH = "~Showing result for \"%s\". Type \"exit\" to exit the search module~";
const string MESSAGE_CLEAR_SEARCH = "All task with the search term \"%s\" is cleared";
const string MESSAGE_DISPLAY_CONTENTS = "%d. %s";
const string MESSAGE_VIEW_TYPE = "Your current default view type is changed to (%s)";

const string ERROR_INVALID_ADD = "An invalid addition has been inputted. Please try again.";
const string ERROR_INVALID_DELETE = "An invalid deletion has been inputted. Please try again.";
const string ERROR_INVALID_COMMAND_FORMAT = "Invalid command format has been inputted. Please try again";
const string ERROR_INVALID_COMMAND = "Invalid command has been inputted. Please try again";
const string ERROR_SET_INVALID_SAVE_FILE_DIRECTORY = "Invalid inputted file directory";

const string MESSAGE_HELP_TIPS[6] = { 
    "add <task description>", 
    "delete <index>",
    "clear",
    "search <keyword>",
    "undo",
    "edit <task description>"
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
    showToUser(MESSAGE_SAVE_FILE_NAME);
}

void UserInterface::printPromptFirstTimeUserDirectory() {
    showToUser(MESSAGE_SET_SAVE_FILE_DIRECTORY_PROMPT);
}

void UserInterface::printPromptCommand() {	
    cout << COMMAND_PROMPT;
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

    printTaskList(taskList, 0 ,_defaultViewType); //thinking on how to implement 
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
    case 1:
        break;
    default:
        break;
    }
    printDisplayList(taskListType->createDisplayList());
    delete taskListType;

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

string UserInterface::getTaskString(Task* task, int viewType) {
    ViewType *taskListType;

    switch(viewType) {
    case -1:
        taskListType = new ViewType();
        break;
    case 0:
        taskListType = new ViewType0();
        break;
    case 1:
        break;
    default:
        break;
    }

    return taskListType->getTaskString(task);
}

void UserInterface::showToUser(string string) {
    cout << string << endl;
}