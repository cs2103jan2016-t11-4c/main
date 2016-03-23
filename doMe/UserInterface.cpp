//@@author A0130475L
#include "UserInterface.h"

const string UserInterface::DEFAULT_TEXT_FILE_NAME = "doMe.txt";
const string UserInterface::SYSTEM_MODE_CON = "mode CON: COLS=%d lines=%d";
const char UserInterface::MESSAGE_BOX_CHARACTER = '=';
const string UserInterface::MESSAGE_VOID_STRING = "";
int UserInterface::DISPLAY_WIDTH = 80;
int UserInterface::DISPLAY_LENGTH = 25;
const int UserInterface::DEFAULT_WINDOWS_WIDTH = 80;
const int UserInterface::DEFAULT_WINDOWS_LENGTH = 25; 

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
const string UserInterface::MESSAGE_VIEW_TYPE = "Your current default view type is changed to (%d).";
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
UserInterface::UserInterface(void) {
    COORD windowSize;
    windowSize = GetLargestConsoleWindowSize(GetStdHandle(STD_OUTPUT_HANDLE));

    _maxWindowWidth = windowSize.X;
    _maxWindowLength = windowSize.Y;

    _logic = Logic::getInstance();
	_memory = Memory::getInstance();
}

UserInterface::~UserInterface(void) {
}

/****************************************************************/

void UserInterface::setEnvironment() {
    printProgramWelcomePage();
    _taskList = _memory->ramGetTaskList();

    printNotificationWelcome();

}

void UserInterface::executeCommandUntilExit() {
    string stringCommand;
    Command* command;

    do {
        try {
            stringCommand = getStringCommand();
            command = _logic->executeCommand(stringCommand);
            printExecutionMessage(command, VALID_MESSAGE);
        } catch(Exception_InvalidCommand e) {
            printExecutionMessage(e.getCommand(), INVALID_MESSAGE);
            command = e.getCommand();
        }
    } while(command->getCommandType() != EXIT);      
}

void UserInterface::printBeforeMessageDisplay() {
    Chrono time;
    printTaskList(time.getCurrentDate(),_memory->getViewType());
}

void UserInterface::printExecutionMessage(Command* executionMessage, COMMAND_OUTCOME commandOutcome) {
    COMMAND_TYPE commandType = executionMessage->getCommandType();

    switch(commandType) {
    case ADD:
        printNotificationAdd(executionMessage, commandOutcome);
        break;
    case DISPLAY:
        showToUser("no display UI");
        break;
    case DEL:
        printNotificationDelete(executionMessage, commandOutcome);
        break;
    case EDIT:
        printNotificationEdit(executionMessage, commandOutcome);
        break;
    case CLEAR:
        printNotificationClear(executionMessage, commandOutcome);
        break;
    case UNDO:
        printBeforeMessageDisplay();
        showToUser(MESSAGE_UNDO_COMMAND);
        break;
    case SORT:
        showToUser("auto sort?");
        break;
    case SEARCH:
        printNotificationSearchTerm(executionMessage, commandOutcome);
        break;
    case ENDSEARCH:
        printNotificationEndSearch(executionMessage, commandOutcome);
        break;
    case VIEWTYPE:
        printNotificationViewType(executionMessage, commandOutcome);
        break;
    case SAVEDIRECTORY:
        printNotificationChangeSaveFileDirectory(executionMessage, commandOutcome);
        break;
    case EXIT:
        //showToUser("Do I even need a exiting message? Nope");
        break;
    case INVALID:
        printNotificationInvalidCommand(executionMessage, commandOutcome);
        break;
    default:
        break;

    }
}

/****************************************************************/

void UserInterface::printNotificationUndo(Command* executionMessage) {
    COMMAND_TYPE commandType = executionMessage->getCommandType();
    printBeforeMessageDisplay();
    switch(commandType) {
    case ADD:
        showToUser(MESSAGE_UNDO_COMMAND);
        break;
    case DISPLAY:
        showToUser("no display UI");
        break;
    case DEL:
        showToUser(MESSAGE_UNDO_COMMAND);
        break;
    case EDIT:
        showToUser(MESSAGE_UNDO_COMMAND);
        break;
    case CLEAR:
        showToUser(MESSAGE_UNDO_COMMAND);
        break;
    case UNDO:
        showToUser(MESSAGE_UNDO_COMMAND);
        //invalidNotificationUndo();
        break;
    case SORT:
        showToUser("auto sort?");
        break;
    case SEARCH:
        showToUser(MESSAGE_UNDO_COMMAND);
        break;
    case ENDSEARCH:
        showToUser(MESSAGE_UNDO_COMMAND);
        break;
    case VIEWTYPE:
        showToUser(MESSAGE_UNDO_COMMAND);
        break;
    case SAVEDIRECTORY:
        showToUser(MESSAGE_UNDO_COMMAND);
        break;
    case EXIT:
        //showToUser("Do I even need a exiting message? Nope");
        break;
    case INVALID:
        showToUser(MESSAGE_UNDO_COMMAND);
        break;
    default:
        showToUser(MESSAGE_UNDO_COMMAND);
        break;
    }
}

void UserInterface::printNotificationAdd(Command* executionMessage, COMMAND_OUTCOME commandOutcome) {
    printBeforeMessageDisplay();
    switch(commandOutcome) {
    case VALID_MESSAGE:
        validNotificationAdd(executionMessage->getTask(), _memory->getViewType(), _memory->getTextFileName());
        break;
    case INVALID_MESSAGE:
        invalidNotificationAdd();
        break;
    case UNDO_MESSAGE:
        printNotificationUndo(executionMessage);
        break;
    }

}

void UserInterface::printNotificationDelete(Command* executionMessage, COMMAND_OUTCOME commandOutcome) {
    printBeforeMessageDisplay();
    switch(commandOutcome) {
    case VALID_MESSAGE:
        validNotificationDelete(executionMessage->getTask(), _memory->getViewType(), _memory->getTextFileName());
        break;
    case INVALID_MESSAGE:
        invalidNotificationDelete();
        break;
    case UNDO_MESSAGE:
        printNotificationUndo(executionMessage);
        break;
    }
}

void UserInterface::printNotificationEdit(Command* executionMessage, COMMAND_OUTCOME commandOutcome) {
    printBeforeMessageDisplay();
    switch(commandOutcome) {
    case VALID_MESSAGE:
        validNotificationEdit(executionMessage->getTask(), _memory->getViewType());
        break;
    case INVALID_MESSAGE:
        invalidNotificationEdit();
        break;
    case UNDO_MESSAGE:
        printNotificationUndo(executionMessage);
        break;
    }
}

void UserInterface::printNotificationClear(Command* executionMessage, COMMAND_OUTCOME commandOutcome) {
    printBeforeMessageDisplay();
    switch(commandOutcome) {
    case VALID_MESSAGE:
        validNotificationClear(_memory->getTextFileName());
        break;
    case INVALID_MESSAGE:
        showToUser("No Invalid Clear");
        break;
    case UNDO_MESSAGE:
        printNotificationUndo(executionMessage);
        break;
    }
}

void UserInterface::printNotificationSearchTerm(Command* executionMessage, COMMAND_OUTCOME commandOutcome) {
    string searchTerm;
    searchTerm = executionMessage->getSearchTerm();
    printSearchList(searchTerm, _memory->getViewType());
    switch(commandOutcome) {
    case VALID_MESSAGE:
        validNotificationSearchTerm(searchTerm);
        break;
    case INVALID_MESSAGE:
        showToUser("No Invalid Search");
        break;
    case UNDO_MESSAGE:
        printNotificationUndo(executionMessage);
        break;
    }
}

void UserInterface::printNotificationEndSearch(Command* executionMessage, COMMAND_OUTCOME commandOutcome) {
    printBeforeMessageDisplay();
    switch(commandOutcome) {
    case VALID_MESSAGE:
        validNotificationExitSearch();
        break;
    case INVALID_MESSAGE:
        showToUser("No Invalid Exit Search");
        break;
    case UNDO_MESSAGE:
        printNotificationUndo(executionMessage);
        break;
    }
}

void UserInterface::printNotificationViewType(Command* executionMessage, COMMAND_OUTCOME commandOutcome) {
    printBeforeMessageDisplay();
    switch(commandOutcome) {
    case VALID_MESSAGE:
        validNotificationViewType(executionMessage->getViewType());
        break;
    case INVALID_MESSAGE:
        invalidNotificationViewtype();
        break;
    case UNDO_MESSAGE:
        printNotificationUndo(executionMessage);
        break;
    }
}

void UserInterface::printNotificationChangeSaveFileDirectory(Command* executionMessage, COMMAND_OUTCOME commandOutcome) {
    printBeforeMessageDisplay();
    switch(commandOutcome) {
    case VALID_MESSAGE:
        validNotificationChangeSaveFileDirectory(executionMessage->getSaveDirectory());
        break;
    case INVALID_MESSAGE:
        invalidNotificationSaveFileDirectory();
        break;
    case UNDO_MESSAGE:
        printNotificationUndo(executionMessage);
        break;
    }
}

void UserInterface::printNotificationInvalidCommand(Command* executionMessage, COMMAND_OUTCOME commandOutcome) {
    printBeforeMessageDisplay();
    invalidNotificationCommand();
}

/****************************************************************/

string UserInterface::getStringCommand() {
    string command;
    printPromptCommand();
    getline(cin, command);
    return command;
}

void UserInterface::printProgramWelcomePage() {
    setDefaultWindowsRowsColumns();
    string space = "               ";
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << space; cout << "                   Welcome to" << endl; 
    cout << space; cout << "      _         __  __                          " << endl;
    cout << space; cout << "     | |       |  \\/  |                         " << endl;
    cout << space; cout << "   __| |  ___  | \\  / |  ___     ___ __  __ ___ " << endl;
    cout << space; cout << "  / _` | / _ \\ | |\\/| | / _ \\   / _ \\  \\/ // _ \\" << endl;
    cout << space; cout << " | (_| || (_) || |  | ||  __/ _|  __/ >  <|  __/" << endl;
    cout << space; cout << "  \\__,_| \\___/ |_|  |_| \\___|(_)\\___|/_/\\_\\___|" << endl;

    cout << endl;
    cout << space; cout << "          <Press any key to continue>" << endl;
    cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
    _getch();
}

void UserInterface::printNotificationWelcome() {
    printBeforeMessageDisplay();
    showToUser(MESSAGE_WELCOME);
}

/****************************************************************/

void UserInterface::printPromptCommand() {
    showToUserMessageBox();
    cout << MESSAGE_COMMAND_PROMPT;
}

/****************************************************************/

void UserInterface::validNotificationAdd(Task* task, int viewType, string textFileName) {
    string taskString;
    taskString = getTaskString(task,viewType);
    sprintf_s(buffer, MESSAGE_ADD.c_str(),taskString.c_str(), textFileName.c_str());
    showToUser(buffer);
}

void UserInterface::validNotificationDelete(Task* task, int viewType, string textFileName) {
    string taskString;
    taskString = getTaskString(task,viewType);
    sprintf_s(buffer, MESSAGE_DELETE.c_str(),taskString.c_str(), textFileName.c_str());
    showToUser(buffer);
}

void UserInterface::validNotificationEdit(Task* task, int viewType) {
    string taskString;
    taskString = getTaskString(task,viewType);
    sprintf_s(buffer, MESSAGE_EDIT.c_str(),taskString.c_str());
    showToUser(buffer);
}

void UserInterface::validNotificationClear(string textFileName) {
    sprintf_s(buffer, MESSAGE_CLEAR.c_str(), textFileName.c_str());
    showToUser(buffer);
}

void UserInterface::validNotificationSearchTerm(string searchTerm) {
    sprintf_s(buffer, MESSAGE_SEARCH.c_str(), searchTerm.c_str());
    showToUser(buffer);
}

void UserInterface::validNotificationExitSearch() {
    sprintf_s(buffer, MESSAGE_EXIT_SEARCH.c_str());
    showToUser(buffer);
}

void UserInterface::validNotificationViewType(int newViewType) {
    sprintf_s(buffer, MESSAGE_VIEW_TYPE.c_str(), newViewType);
    showToUser(buffer);
}

void UserInterface::validNotificationChangeSaveFileDirectory(string newDirectory) {
    sprintf_s(buffer, MESSAGE_SET_SAVE_FILE_DIRECTORY.c_str(), newDirectory.c_str());
    showToUser(buffer);
}


/****************************************************************/

void UserInterface::invalidNotificationAdd() {
    showToUser(ERROR_INVALID_ADD);
}

void UserInterface::invalidNotificationDelete() {
    showToUser(ERROR_INVALID_DELETE);
}

void UserInterface::invalidNotificationEdit() {
    showToUser(ERROR_INVALID_EDIT);
}

void UserInterface::invalidNotificationViewtype() {
    showToUser(ERROR_INVALID_VIEWTYPE);
}

void UserInterface::invalidNotificationSaveFileDirectory() {
    showToUser(ERROR_SET_INVALID_SAVE_FILE_DIRECTORY);
}

void UserInterface::invalidNotificationCommand() {
    showToUser(ERROR_INVALID_COMMAND);
}

void UserInterface::invalidNotificationUndo() {
    showToUser(ERROR_INVALID_UNDO);
}

/****************************************************************/

void UserInterface::printSearchList(string searchTerm, int viewType) {
    ViewType* taskListType;

    switch(viewType) {
    case 1:
        taskListType = new ViewType1(_taskList);
        break;
    case 2:
        taskListType = new ViewType2(_taskList);
        break;
    default:
        taskListType = new ViewType(_taskList);
        break;
    }
    printDisplayList(createDisplayBox(taskListType->createDisplayList()));
    delete taskListType;
}

void UserInterface::printTaskList(int currentDate ,int viewType) {
    ViewType* taskListType;

    switch(viewType) {
    case 1:
        taskListType = new ViewType1(_taskList , currentDate);
        break;
    case 2:
        taskListType = new ViewType2(_taskList , currentDate);
        break;
    default:
        taskListType = new ViewType(_taskList , currentDate);
        break;
    }

    printDisplayList(createDisplayBox(taskListType->createDisplayList()));
    delete taskListType;
}

/****************************************************************/

string UserInterface::getTaskString(Task* task, int viewType) {
    ViewType* taskListType;

    switch(viewType) {
    case 1:
        taskListType = new ViewType1();
        break;
    case 2:
        taskListType = new ViewType2();
        break;
    default:
        taskListType = new ViewType();
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


void UserInterface::showToUser(string message) {
    cout << message << endl;
}

void UserInterface::showToUserMessageBox() {
    string messageBox;
    //setWindowsRowsColumns(0);
    messageBox.assign(DISPLAY_WIDTH,MESSAGE_BOX_CHARACTER);
    messageBox.pop_back();

    showToUser(messageBox);
}

void UserInterface::setWindowsRowsColumns(int size) {
    //system("mode CON: COLS=120 lines=40");
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;
    int rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    DISPLAY_WIDTH = columns;
    DISPLAY_LENGTH = rows - 4;

    if(size < _maxWindowLength) {
        if(size > DISPLAY_LENGTH) {
            sprintf_s(buffer, SYSTEM_MODE_CON.c_str(), columns , rows+1);
            system(buffer);
            DISPLAY_LENGTH++;
        }
    } 
}

void UserInterface::setDefaultWindowsRowsColumns() {
    sprintf_s(buffer, SYSTEM_MODE_CON.c_str(), DEFAULT_WINDOWS_WIDTH , DEFAULT_WINDOWS_LENGTH);
    system(buffer);
}

vector<string> UserInterface::createDisplayBox(vector<string> displayList) {
    vector<string>::iterator displayListIter;
    string messageBox;

    setWindowsRowsColumns(displayList.size()+2);
    messageBox.assign(DISPLAY_WIDTH,MESSAGE_BOX_CHARACTER);
    messageBox.pop_back();

    displayList.insert(displayList.begin(),messageBox);
    displayList.insert(displayList.begin(),MESSAGE_VOID_STRING);
    displayListIter = displayList.begin();
    displayListIter++;

    while(displayList.size() < DISPLAY_LENGTH) {
        displayList.push_back(MESSAGE_VOID_STRING);
    }

    displayList.insert(displayList.end(),messageBox);
    return displayList;
}

/*************************Unused*********************************/
/****************************************************************/

void UserInterface::printNotificationEmpty(string textFileName) {
    sprintf_s(buffer, MESSAGE_EMPTY.c_str(), textFileName.c_str());
    showToUser(buffer);
}

void UserInterface::printNotificationClearSearch(string searchTerm) {
    sprintf_s(buffer, MESSAGE_CLEAR_SEARCH.c_str(), searchTerm.c_str());
    showToUser(buffer);
}

void UserInterface::printPromptFirstTimeUser() {
    showToUser(MESSAGE_FIRST_TIME);
    cout << MESSAGE_SAVE_FILE_NAME;
}

void UserInterface::printPromptFirstTimeUserDirectory() {
    cout << MESSAGE_SET_SAVE_FILE_DIRECTORY_PROMPT;
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

void UserInterface::printNotificationEmptySaveFileDirectory() {
    showToUser(MESSAGE_EMPTY_SAVE_FILE_DIRECTORY);
    showToUser(MESSAGE_TIP_SAVE_FILE_DIRECTORY);
}