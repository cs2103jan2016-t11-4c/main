//@@author A0130475L
#include "UserInterface.h"

const string UserInterface::SYSTEM_MODE_CON = "mode CON: COLS=%d lines=%d";
const char UserInterface::MESSAGE_BOX_CHARACTER = '=';
const string UserInterface::MESSAGE_VOID_STRING = "";
string UserInterface::MESSAGE_WELCOME = "Welcome to doMe. Your programme is ready for use.";
int UserInterface::DISPLAY_WIDTH = 80;
int UserInterface::DISPLAY_LENGTH = 25;

const string UserInterface::MESSAGE_FIRST_TIME = "This is your first time using this programme.";
const string UserInterface::MESSAGE_SAVE_FILE_NAME = "Input your save file name: ";
const string UserInterface::MESSAGE_SET_SAVE_FILE_DIRECTORY_PROMPT = "Set your save file directory: ";
const string UserInterface::MESSAGE_EMPTY_SAVE_FILE_DIRECTORY = "Your file is save at the current directory.";
const string UserInterface::MESSAGE_TIP_SAVE_FILE_DIRECTORY = "You can change your directory later.";

const string UserInterface::MESSAGE_COMMAND_PROMPT = "command: ";

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
    COORD windowSize;
    windowSize = GetLargestConsoleWindowSize(GetStdHandle(STD_OUTPUT_HANDLE));

    _maxWindowWidth = windowSize.X;
    _maxWindowLength = windowSize.Y;

    _commandFeedback = Command_Feedback::getInstance();
    _logic = Logic::getInstance();
    _memory = Memory::getInstance();
    _taskList = _memory->ramGetTaskList();
}

UserInterface::~UserInterface(void) {
}

/****************************************************************/

void UserInterface::setEnvironment() {
    printProgramWelcomePage();
    try {
        _memory->loadSettings();
    } catch(Exception_FileCannotOpen e) {
        MESSAGE_WELCOME = e.getString();
    }
    try {
        _memory->loadRam();
    } catch(Exception_FileCannotOpen e) {
        MESSAGE_WELCOME = e.getString();
    }

    int length,width;
    _memory->getWindowSize(width,length);
    resizeWindow(width,length);

    printNotificationWelcome();
}

void UserInterface::printProgramWelcomePage() {
    system("Color 08");
    resizeWindow(DISPLAY_WIDTH,DISPLAY_LENGTH);
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
    printDefaultDisplay();
    showToUser(MESSAGE_WELCOME);
}

/****************************************************************/

void UserInterface::printPromptCommand() {
    showToUserMessageBox();
    cout << MESSAGE_COMMAND_PROMPT;
}

string UserInterface::getStringCommand() {
    string command;
    printPromptCommand();
    getline(cin, command);
    return command;
}

void UserInterface::executeCommandUntilExit() {
    string stringCommand;
    Command* command;

    do {
        try {
            stringCommand = getStringCommand();
            LOG(__FILE__,"User enters: \" " + stringCommand + "\"");
            command = _logic->executeCommand(stringCommand);

            printMessageDisplay(command);
            printExecutionMessage(command, VALID_MESSAGE);
        } catch(Exception_InvalidCommand e) {
            command = e.getCommand();
            printMessageDisplay(command);
            printExecutionMessage(command, INVALID_MESSAGE);
            
        }
    } while(command->getCommandType() != EXIT);      
}

void UserInterface::printMessageDisplay(Command* command) {

    CommandType commandType = command->getCommandType();

    switch(commandType) {
    case SEARCH:
        printSearchDisplay();
        break;
    default:
        printDefaultDisplay();
        break;
    }
}

void UserInterface::printDefaultDisplay() {
    printTaskList(DATE, _memory->getViewType());
}

void UserInterface::printSearchDisplay() {
    printSearchList(DATE, _memory->getViewType());
}

void UserInterface::printExecutionMessage(Command* executionMessage, CommandOutcome commandOutcome) {
    string message;
    message = _commandFeedback->getCommandFeedback(executionMessage, commandOutcome, _memory->getViewType());
    showToUser(message);

}

/****************************************************************/

void UserInterface::printSearchList(int currentDate, int viewType) {
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
    printDisplayList(createDisplayBox(taskListType->createSearchList()));

    delete taskListType;
}

void UserInterface::printTaskList(int currentDate, int viewType) {
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

void UserInterface::resizeWindow(int width, int length) {
    sprintf_s(buffer, SYSTEM_MODE_CON.c_str(), width, length);
    system(buffer);
}

void UserInterface::setWindowsRowsColumns(int size) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int width;
    int length;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    length = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    DISPLAY_WIDTH = width;
    DISPLAY_LENGTH = length - 4;

    while((size < _maxWindowLength) && (size > DISPLAY_LENGTH)) {
        if(size < _maxWindowLength) {
            if(size > DISPLAY_LENGTH) {
                resizeWindow(width,length+1);
                DISPLAY_LENGTH++;
            }
        } 
    }
    _memory->changeWindowSize(DISPLAY_WIDTH,DISPLAY_LENGTH + 4);
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

void UserInterface::printPromptHelp() {
    size_t size = (sizeof(MESSAGE_HELP_TIPS)/sizeof(*MESSAGE_HELP_TIPS));
    vector<string> helpList(MESSAGE_HELP_TIPS,MESSAGE_HELP_TIPS+size);
    vector<string>::iterator helpListIter = helpList.begin();

    while(helpListIter!= helpList.end()) {
        showToUser(*helpListIter);
        helpListIter++;
    }
}
