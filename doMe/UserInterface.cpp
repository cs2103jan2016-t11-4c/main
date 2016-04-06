//@@author A0130475L
#include "UserInterface.h"

const string UserInterface::SYSTEM_MODE_CON = "mode CON: COLS=%d lines=%d";
const string UserInterface::SYSTEM_COLOUR = "Color 0F";
const char UserInterface::MESSAGE_BOX_CHARACTER = '=';
const string UserInterface::MESSAGE_VOID_STRING = "";
const string UserInterface::MESSAGE_WELCOME = "Welcome to doMe. Your programme is ready for use.";
unsigned int UserInterface::DISPLAY_WIDTH = 80;
unsigned int UserInterface::DISPLAY_LENGTH = 25;
unsigned int UserInterface::DISPLAY_BOX_WIDTH = 80;
unsigned int UserInterface::DISPLAY_BOX_LENGTH = 25;
const int UserInterface::DISPLAY_DEFAULT_WIDTH = 80;
const int UserInterface::DISPLAY_DEFAULT_LENGTH = 25;
const int UserInterface::DISPLAY_SYNC_WIDTH = 0;
const int UserInterface::DISPLAY_SYNC_LENGTH = 6;

const string UserInterface::MESSAGE_FIRST_TIME = "This is your first time using this programme.";
const string UserInterface::MESSAGE_SAVE_FILE_NAME = "Input your save file name: ";
const string UserInterface::MESSAGE_SET_SAVE_FILE_DIRECTORY_PROMPT = "Set your save file directory: ";
const string UserInterface::MESSAGE_EMPTY_SAVE_FILE_DIRECTORY = "Your file is save at the current directory.";
const string UserInterface::MESSAGE_TIP_SAVE_FILE_DIRECTORY = "You can change your directory later.";
const string UserInterface::MESSAGE_COMMAND_PROMPT = "command: ";
const string UserInterface::MESSAGE_DEFAULT_DIRECTORY = "DEFAULT";
const string UserInterface::MESSAGE_DIRECTORY_BOX = "<%s>";

const string UserInterface::COLOUR_DEFAULT = "DEFAULT";
const string UserInterface::COLOUR_NEW = "NEW";
const string UserInterface::COLOUR_DONE = "DONE";
const string UserInterface::COLOUR_SEARCH = "SEARCH";
const string UserInterface::COLOUR_HELP = "HELP";
/*
const string UserInterface::MESSAGE_HELP_TIPS[] = { 
"add <task description>", 
"delete <index>",
"clear",
"edit <index> <task description>",
"search <keyword>",
"change <directory>",
"undo",
"redo",
"change directory <directory>",
"viewtype <index>",
"help",
"exit"
}; 
*/
const string UserInterface::MESSAGE_HELP_TIPS[] = {
    "",
    "                            +-----------------------------------------------+",
    "   Adding a task            |              OPTIONAL PARAMETERS*             |",
    "   +----------+-------------+--------------------+--------------+-----------+",
    "   | MODIFIER | TASK NAME   | DATE               | TIME         | LOCATION  |",
    "   +----------+-------------+--------------------+--------------+-----------+",
    "   | <empty>  | Cycling     | 14/02/2016         | 1100         | @Florist  |",
    "   | add      | Buy flowers | 14/02/16           | 2359         | @the park |",
    "   | a        |             | 14/02              | 11am         |           |",
    "   |          |             | 14 Feb             | 1159pm       |           |",
    "   |          |             | 14 Feb to 16 Feb   | 1100 to 2359 |           |",
    "   |          |             | 14 Feb - 16 Feb    | 1100 - 2359  |           |",
    "   |          |             |                    |              |           |",
    "   |          |             | today              |              |           |",
    "   |          |             | tmr, tomorrow      |              |           |",
    "   |          |             | mon, tue...        |              |           |",
    "   |          |             | monday, tuesday... |              |           |",
    "   |          |             | next mon           |              |           |",
    "   |          |             | next tuesday       |              |           |",
    "   |          |             | mon to wed         |              |           |",
    "   |          |             | mon - wed          |              |           |",
    "   |          |             |                    |              |           |",
    "   +----------+-------------+--------------------+--------------+-----------+",
    "",
    "  *Optional parameters can be input in any order eg. \"cycling 7pm @park today\"."
    "",
    "",
    "===============================================================================",
    "",
    "",
    "              Deleting Task           +------------------------+",
    "              & Task Parameters       |   OPTIONAL PARAMETERS  |",
    "              +----------+------------+------+------+----------+",
    "              | MODIFIER | TASK INDEX | DATE | TIME | LOCATION |",
    "              +----------+------------+------+------+----------+",
    "              | delete   | <empty>*   | date | time | location |",
    "              | del      | 1          | d    | t    | l        |",
    "              | d        | 12         |      |      |          |",
    "              |          | 1-12       |      |      |          |",
    "              |          | 1 - 12     |      |      |          |",
    "              |          |            |      |      |          |",
    "              |          |            |      |      |          |",
    "              | clear    | <empty>**  | n/a  | n/a  | n/a      |",
    "              |          | 1          |      |      |          |",
    "              |          | 12         |      |      |          |",
    "              |          | 1-12       |      |      |          |",
    "              |          | 1 - 12     |      |      |          |",
    "              |          |            |      |      |          |",
    "              +----------+------------+------+------+----------+",
    "",
    "           *Deleting <empty> index directs program to Last Added Task.",
    "           **Clearing <empty> index clears all tasks in view.",
    "",
    "",
    "===============================================================================",
    "",
    "",
    "      Editting                +-------------------------------------------+",
    "      a Task                  |           ADDITIONAL PARAMETERS           |",
    "      +----------+------------+------------+------------------+-----------+",
    "      | MODIFIER | TASK INDEX | TASK NAME  | DATE & TIME      | LOCATION  |",
    "      +----------+------------+------------+------------------+-----------+",
    "      | edit     | <empty>*   | <new name> | <date>           | @location |",
    "      | change   | 1          |            | <date> to <date> |           |",
    "      | update   | 12         |            | <time>           |           |",
    "      | e, c     |            |            | <time> to <time> |           |",
    "      |          |            |            |                  |           |",
    "      +----------+------------+------------+------------------+-----------+",
    "",
    "",
    "                *<empty> index directs program to Last Added Task.",
    "                **edits Second Date of Task.",
    "",
    "",
    "===============================================================================",
    "",
    "                          Press any key to continue",
    "",

};

UserInterface::UserInterface(void) {
    system(SYSTEM_COLOUR.c_str());
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
    setConsoleColorDefault();
    printProgramWelcomePage();
    vector<string> welcomeStringVector;

    try {
        _memory->loadSettings();
    } catch(Exception_FileCannotOpen e) {
        welcomeStringVector.push_back(e.getString());
    }
    try {
        _memory->loadRam();
    } catch(Exception_FileCannotOpen e) {
        welcomeStringVector.push_back(e.getString());
    }

    if(welcomeStringVector.empty()) {
        welcomeStringVector.push_back(MESSAGE_WELCOME);
    }

    int length,width;
    _memory->getWindowSize(width,length);
    resizeWindow(width,length);

    printNotificationWelcome(welcomeStringVector);
}

void UserInterface::printProgramWelcomePage() {
    resizeWindow(DISPLAY_DEFAULT_WIDTH, DISPLAY_DEFAULT_LENGTH);
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

void UserInterface::printNotificationWelcome(vector<string> welcomeStringVector) {
    printDefaultDisplay();
    vector<string>::iterator welcomeStringIter = welcomeStringVector.begin();
    while(welcomeStringIter != welcomeStringVector.end()){
        showToUser(*welcomeStringIter);
        welcomeStringIter++;
    }
}

/****************************************************************/

void UserInterface::printPromptCommand() {
    showToUserMessageBox();
    printCurrentDirectory();
    cout << MESSAGE_COMMAND_PROMPT;
}

void UserInterface::printCurrentDirectory() {
    string saveDirectory = _memory->getSaveDirectory();
    if(saveDirectory.empty()) {
        sprintf_s(buffer, MESSAGE_DIRECTORY_BOX.c_str(), MESSAGE_DEFAULT_DIRECTORY.c_str());
    } else {
        sprintf_s(buffer, MESSAGE_DIRECTORY_BOX.c_str(), (_memory->getSaveDirectory()).c_str());
    }
    showToUser(buffer);
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

/****************************************************************/

void UserInterface::printMessageDisplay(Command* command) {

    CommandType commandType = command->getCommandType();
    Command* commandRedo;

    switch(commandType) {
    case SEARCH:
        _lastDisplayType = SEARCH_DISPLAY;
        printDisplayType(SEARCH_DISPLAY);
        break;
    case HELP:
        _lastDisplayType = HELP_DISPLAY;
        printDisplayType(HELP_DISPLAY);
        break;
    case EXIT:
        break;
    case INVALID:
        printDisplayType(_lastDisplayType);
        break;
    case REDO:
        commandRedo = command->getRedoneCommand();
        if(commandRedo) {
            printDisplayType(DEFAULT_DISPLAY);
        } else {
            printMessageDisplay(commandRedo);
        }
        break;
    default:
        _lastDisplayType = DEFAULT_DISPLAY;
        printDisplayType(DEFAULT_DISPLAY);
        break;
    }
}

void UserInterface::printDisplayType(DisplayType display) {
    switch(display) {
    case SEARCH_DISPLAY:
        printSearchDisplay();
        break;
    case HELP_DISPLAY:
        printHelpDisplay();
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

void UserInterface::printHelpDisplay() {
    printHelpList(DATE, _memory->getViewType());
}

void UserInterface::printExecutionMessage(Command* executionMessage, CommandOutcome commandOutcome) {
    string message;
    message = _commandFeedback->getCommandFeedback(executionMessage, commandOutcome, _memory->getViewType());
    showToUser(message);

}

/****************************************************************/

void UserInterface::printTaskList(int currentDate, int viewType) {
    ViewType* taskListType;
    vector<string> displayList;
    vector<string> colourCoding;

    switch(viewType) {
    case 1:
        taskListType = new ViewType1(_taskList , currentDate);
        break;
    case 2:
        taskListType = new ViewType2(_taskList , currentDate);
        break;
    case 3:
        taskListType = new ViewType3(_taskList , currentDate);
        break;
    default:
        taskListType = new ViewType(_taskList , currentDate);
        break;
    }
    displayList = taskListType->createDisplayList();
    colourCoding = taskListType->getColourCoding();

    displayList = createDisplayBox(displayList);
    colourCoding = synchronizeColourCodingWithDisplayBox(colourCoding);

    printList(displayList, colourCoding);
    delete taskListType;
}

void UserInterface::printSearchList(int currentDate, int viewType) {
    ViewType* taskListType;

    switch(viewType) {
    case 1:
        taskListType = new ViewType1(_taskList);
        break;
    case 2:
        taskListType = new ViewType2(_taskList);
        break;
    case 3:
        taskListType = new ViewType3(_taskList , currentDate);
        break;
    default:
        taskListType = new ViewType(_taskList);
        break;
    }

    changeListColour(COLOUR_SEARCH);
    printList(createDisplayBox(taskListType->createSearchList()));
    //changeListColour(COLOUR_DEFAULT);

    delete taskListType;
}

void UserInterface::printHelpList(int currentDate, int viewType) {
    size_t size = (sizeof(MESSAGE_HELP_TIPS)/sizeof(*MESSAGE_HELP_TIPS));
    vector<string> helpList(MESSAGE_HELP_TIPS,MESSAGE_HELP_TIPS+size);

    changeListColour(COLOUR_HELP);
    /*
    HelpPrompt* helpPrompt;
    helpPrompt = HelpPrompt::getInstance();
    vector<vector<string>*>* helpPromptList;
    helpPromptList = helpPrompt->getHelpList();

    vector<vector<string>*>::iterator helpListIter = helpPromptList->begin();
    while(helpListIter != helpPromptList->end()) {
    printList(createDisplayBox(*(*helpListIter)));
    _getch();
    helpListIter++;
    }
    */
    printList(createDisplayBox(helpList));
    _getch();

    printTaskList(currentDate, viewType);
    _lastDisplayType = DEFAULT_DISPLAY;
}

/****************************************************************/

void UserInterface::printList(vector<string> displayList) {
    vector<string>::iterator displayListIter = displayList.begin();

    while(displayListIter != displayList.end()) {
        showToUser(*displayListIter);
        displayListIter++;
    }
}

void UserInterface::printList(vector<string> displayList, vector<string> colourCoding) {
    vector<string>::iterator displayListIter = displayList.begin();
    vector<string>::iterator colourCodingIter = colourCoding.begin();

    while(displayListIter != displayList.end()) {
        changeListColour(*colourCodingIter);
        showToUser(*displayListIter);
        displayListIter++;
        if(colourCodingIter != colourCoding.end()-1) {
            colourCodingIter++;
        }
    }
}

/****************************************************************/

vector<string> UserInterface::createDisplayBox(vector<string> displayList) {
    vector<string>::iterator displayListIter;
    string messageBox;
    COORD c;

    setWindowsRowsColumns(displayList.size());
    messageBox.assign(DISPLAY_WIDTH, MESSAGE_BOX_CHARACTER);
    messageBox.pop_back();

    displayList.insert(displayList.begin(),messageBox);
    displayList.insert(displayList.begin(),MESSAGE_VOID_STRING);
    displayListIter = displayList.begin();
    displayListIter++;

    while(displayList.size() < DISPLAY_BOX_LENGTH) {
        displayList.push_back(MESSAGE_VOID_STRING);
    }
    displayList.insert(displayList.end(),messageBox);

    c.X = DISPLAY_WIDTH;
    c.Y = (displayList.size()+3);
    SetConsoleScreenBufferSize(GetStdHandle( STD_OUTPUT_HANDLE), c);

    return displayList;
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

/****************************************************************/

void UserInterface::resizeWindow(int width, int length) {
    sprintf_s(buffer, SYSTEM_MODE_CON.c_str(), width, length);
    system(buffer);
}

void UserInterface::setWindowsRowsColumns(int size) {
    resizeWindow(DISPLAY_DEFAULT_WIDTH, DISPLAY_DEFAULT_LENGTH);

    DISPLAY_LENGTH = getBiggerDisplaySize(DISPLAY_DEFAULT_LENGTH, size + DISPLAY_SYNC_LENGTH);

    synchronizeWindowsDisplaySize(DISPLAY_WIDTH, DISPLAY_LENGTH);
    resizeWindow(DISPLAY_WIDTH, DISPLAY_LENGTH);
    _memory->changeWindowSize(DISPLAY_WIDTH, DISPLAY_LENGTH);

    /*current window size
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    length = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    */
}

int UserInterface::getBiggerDisplaySize(int size1, int size2) {
    if(size1 < size2) {
        return size2;
    } else {
        return size1;
    }
}

void UserInterface::synchronizeWindowsDisplaySize(int width, int length) {
    DISPLAY_BOX_WIDTH = width - DISPLAY_SYNC_WIDTH;
    DISPLAY_BOX_LENGTH = length - DISPLAY_SYNC_LENGTH + 2;
    length = DISPLAY_BOX_LENGTH;
}

/****************************************************************/

vector<string> UserInterface::synchronizeColourCodingWithDisplayBox(vector<string> colourCoding) {
    int i = 0;
    while(i < 2) {
        colourCoding.insert(colourCoding.begin(),COLOUR_DEFAULT);
        i++;
    }
    colourCoding.insert(colourCoding.end(),COLOUR_DEFAULT);
    return colourCoding;
}

void UserInterface::changeListColour(string colourCoding) {
    if(colourCoding == COLOUR_NEW) {
        setConsoleColor(BLACK, LIGHT_RED);
        return;
    } else {
        if(colourCoding == COLOUR_DONE) {
            setConsoleColor(BLACK, GRAY);
            return;
        } else {
            if(colourCoding == COLOUR_SEARCH) {
                setConsoleColor(BLACK, LIGHT_GREEN);
                return;
            } else {
                if(colourCoding == COLOUR_HELP) {
                    setConsoleColor(BLACK, LIGHT_YELLOW);
                    return;
                }
            }
        }
    }
    setConsoleColorDefault();
}

void UserInterface::setConsoleColor(int background, int foreground) {
    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int colour = background * 16 + foreground;
    SetConsoleTextAttribute(hConsole, colour);
}

void UserInterface::setConsoleColorDefault() {
    setConsoleColor(BLACK, LIGHT_WHITE);
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


