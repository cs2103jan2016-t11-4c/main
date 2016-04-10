//@@author A0130475L
#include "UserInterface.h"

const string UserInterface::SYSTEM_MODE_CON = "mode CON: COLS=%d lines=%d";
const string UserInterface::SYSTEM_COLOUR = "Color 0F";
const char UserInterface::MESSAGE_BOX_CHARACTER = '=';
const string UserInterface::MESSAGE_VOID_STRING = "";
const string UserInterface::MESSAGE_WELCOME = "Welcome to doMe. Your programme is ready for use.";
unsigned int UserInterface::DISPLAY_WIDTH = 80;
unsigned int UserInterface::DISPLAY_LENGTH = 35;
unsigned int UserInterface::DISPLAY_BOX_WIDTH = 80;
unsigned int UserInterface::DISPLAY_BOX_LENGTH = 35;
const int UserInterface::DISPLAY_DEFAULT_WIDTH = 80;
const int UserInterface::DISPLAY_DEFAULT_LENGTH = 25;
const int UserInterface::DISPLAY_SYNC_WIDTH = 0;
const int UserInterface::DISPLAY_SYNC_LENGTH = 5;

const string UserInterface::MESSAGE_COMMAND_PROMPT = "command: ";
const string UserInterface::MESSAGE_DEFAULT_DIRECTORY = "Default Directory";
const string UserInterface::MESSAGE_DIRECTORY_BOX = "<%s>";

const string UserInterface::COLOUR_DEFAULT = "DEFAULT";
const string UserInterface::COLOUR_NEW = "NEW";
const string UserInterface::COLOUR_DONE = "DONE";
const string UserInterface::COLOUR_SEARCH = "SEARCH";
const string UserInterface::COLOUR_HELP = "HELP";
const string UserInterface::COLOUR_CATEGORY = "CATEGORY";
const string UserInterface::COLOUR_FEEDBACK = "FEEDBACK";

const string UserInterface::MESSAGE_WELCOME_SCREEN[] = {
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"                                  Welcome to",
	"                     _         __  __                          ",
	"                    | |       |  \\/  |                         ",
	"                  __| |  ___  | \\  / |  ___     ___ __  __ ___ ",
	"                 / _` | / _ \\ | |\\/| | / _ \\   / _ \\  \\/ // _ \\",
	"                | (_| || (_) || |  | ||  __/ _|  __/ >  <|  __/",
	"                 \\__,_| \\___/ |_|  |_| \\___|(_)\\___|/_/\\_\\___|",
	"",
	"                         <Press any key to continue>",
	"",
	"", 
	"", 
	"", 
	"", 
	"", 
	"", 
	"", 
	"",
};

const string UserInterface::MESSAGE_HELP_TIPS[] = {
	"",
	"",
	"===============================================================================",
	"                            List of Available Commands",
	"",
	"                            PRESS ANY KEY TO CONTINUE...",
	"                          (Arrow Keys/PgUp PgDn to Scroll)",
	"===============================================================================",
	"",
	"                                  _   ___  ___  ",
	"                                 /_\\ |   \\|   \\ ",
	"                                / _ \\| |) | |) |",
	"                               /_/ \\_\\___/|___/  eg. \"Jog tmr 6am @the park\"",
	"                            +-----------------------------------------------+",
	"                            |              OPTIONAL PARAMETERS              |",
	"   +----------+-------------+--------------------+--------------+-----------+",
	"   | MODIFIER | TASK NAME   | DATE               | TIME         | LOCATION  |",
	"   +----------+-------------+--------------------+--------------+-----------+",
	"   | <empty>  | Cycling     | 14/02/2016         | 1430         | @Florist  |",
	"   | add      | Buy flowers | 14/02/16           | 14.30        | @the park |",
	"   | a        | *tuesday    | 14/02              | 14:30        |           |",
	"   |          |             | 14 Feb             | 11am         |           |",
	"   |          |             | 14 Feb to 16 Feb   | 1430pm       |           |",
	"   |          |             | 14 Feb - 16 Feb    |              |           |",
	"   |          |             | 14 - 16 Feb        | 1100 to 1430 |           |",
	"   |          |             |                    | 1100 - 1430  |           |",
	"   |          |             | today              | 11am - 230pm |           |",
	"   |          |             | tmr, tomorrow      | 11 - 230pm   |           |",
	"   |          |             | mon, monday...     |              |           |",
	"   |          |             | next tuesday       |              |           |",
	"   |          |             | mon to wed         |              |           |",
	"   |          |             | mon - wed          |              |           |",
	"   |          |             | this/next week     |              |           |",
	"   +----------+-------------+--------------------+--------------+-----------+",
	"  - Optional parameters can be typed in any order eg.\"cycling 7pm @park today\".",
	"  - Asterisks turn keywords into normal text eg.\"thank god its *friday\"",
	"  - \"this week\" sets the deadline to be the end of the week, Sunday.",
	"",
	"          ============================================================",
	"",
	"                          ___  ___ _    ___ _____ ___ ",
	"                         |   \\| __| |  | __|_   _| __|",
	"                         | |) | _|| |__| _|  | | | _| ",
	"                         |___/|___|____|___| |_| |___| eg. \"delete 5\"",
	"                                       +------------------------+",
	"                                       |   OPTIONAL PARAMETERS  |",
	"               +----------+------------+------+------+----------+",
	"               | MODIFIER | TASK INDEX | DATE | TIME | LOCATION |",
	"               +----------+------------+------+------+----------+",
	"               | delete   | <empty>*   | date | time | location |",
	"               | del      | 1          | d    | t    | l        |",
	"               | d        | 12         |      |      |          |",
	"               |          | 1-5        |      |      |          |",
	"               |          | 1 - 5      |      |      |          |",
	"               |          | 1 2 3 4 5  |      |      |          |",
	"               |          |            |      |      |          |",
	"               | clear    | <empty>**  | n/a  | n/a  | n/a      |",
	"               |          | 1          |      |      |          |",
	"               |          | 12         |      |      |          |",
	"               |          | 1-12       |      |      |          |",
	"               |          | 1 - 12     |      |      |          |",
	"               |          |            |      |      |          |",
	"               +----------+------------+------+------+----------+",
	"               *Deleting <empty> index deletes Last Added Task.",
	"               **Typing \"clear\" clears all tasks in view.",
	"",
	"          ============================================================",
	"",
	"                                ___ ___ ___ _____ ",
	"                               | __|   \\_ _|_   _|",
	"                               | _|| |) | |  | |  ",
	"                               |___|___/___| |_|   eg. \"edit 1 sleep 12pm\"",
	"                             +-------------------------------------------+",
	"                             |            ADDITIONAL PARAMETERS          |",
	"     +----------+------------+------------+------------------+-----------+",
	"     | MODIFIER | TASK INDEX | TASK NAME  | DATE & TIME      | LOCATION  |",
	"     +----------+------------+------------+------------------+-----------+",
	"     | edit     | <empty>*   | <new name> | <date>           | @location |",
	"     | change   | 1          |            | <date> to <date> |           |",
	"     | update   | 12         |            | <time>           |           |",
	"     | e, c, u  |            |            | <time> to <time> |           |",
	"     |          |            |            |                  |           |",
	"     +----------+------------+------------+------------------+-----------+",
	"     *Editting <empty> index edits Last Added Task.",
	"     **edits Second Date of Task.",
	"",
	"          ============================================================",
	"",
	"              __  __   _   ___ _  __    _   ___   ___   ___  _  _ ___ ",
	"             |  \\/  | /_\\ | _ \\ |/ /   /_\\ / __| |   \\ / _ \\| \\| | __|",
	"             | |\\/| |/ _ \\|   / ' <   / _ \\\\__ \\ | |) | (_) | .` | _| ",
	"             |_|  |_/_/ \\_\\_|_\\_|\\_\\ /_/ \\_\\___/ |___/ \\___/|_|\\_|___|",
	"",
	"                               eg.\"mark 5 as done\"",
	"                     +----------+------------+-------------+",
	"                     | MODIFIER | TASK INDEX | DONE STATUS |",
	"                     +----------+------------+-------------+",
	"                     | <empty>  | <empty>    | done        |",
	"                     | mark     | 1          | as done     |",
	"                     |          | 12         |             |",
	"                     |          |            | not done    |",
	"                     |          |            | as not done | ",
	"                     |          |            | undone      |",
	"                     +----------+------------+-------------+",
	"                    *<empty> index marks Last Added Task as done/undone.",
	"",
	"          ============================================================",
	"",
	"                           ___ ___   _   ___  ___ _  _ ",
	"                          / __| __| /_\\ | _ \\/ __| || |",
	"                          \\__ \\ _| / _ \\|   / (__| __ |",
	"                          |___/___/_/ \\_\\_|_\\\\___|_||_|",
	"",
	"                              eg. \"search car keys\"",
	"                        +------------+-----------------+",
	"                        | MODIFIER   | SEARCH TERM(S)  |",
	"                        +------------+-----------------+",
	"                        | search     | Waldo           |",
	"                        | search for | Nemo Sea        |",
	"                        | s, f       | Meaning in life |",
	"                        |            |                 |",
	"                        +------------+-----------------+",
	"",
	"          ============================================================",
	"",
	"          <Additional Commands>",
	"",
	"          - UNDO a command",
	"",
	"                \"undo\"",
	"                \"u\"",
	"",
	"          - REDO a command",
	"",
	"                \"redo\"",
	"                \"r\"",
	"",
	"          - Changing SAVE DIRECTORY",
	"",
	"                \"cd D:/Top secret folder\"",
	"                \"cd\"          (Changes to the Default Directory)",
	"",
	"          - Changing VIEW",
	"",
	"                \"v 1\"",
	"                \"viewtype 2\"",
	"                \"viewtype 3\"",
	"",
	"",
	"===============================================================================",
	"",
	"                          PRESS ANY KEY TO CONTINUE...",
	"",
	"===============================================================================",
};

UserInterface::UserInterface(void) {
	system(SYSTEM_COLOUR.c_str());
	COORD windowSize;
	windowSize = GetLargestConsoleWindowSize(GetStdHandle(STD_OUTPUT_HANDLE));

	_maxWindowWidth = windowSize.X;
	_maxWindowLength = windowSize.Y;

	_commandFeedback = CommandFeedback::getInstance();
	_logic = Logic::getInstance();
	_memory = Memory::getInstance();
	_taskList = _memory->ramGetTaskList();
}

UserInterface::~UserInterface(void) {
}

/****************************************************************/

void UserInterface::setEnvironment() {
	setConsoleColorDefault();
	vector<string> welcomeStringVector;

	try {
		_memory->loadSettings();
	} catch(Exception_FileCannotOpen e) {
		welcomeStringVector.push_back(e.getString());
	} catch(Exception_FirstTimeUser e) {
		printProgramWelcomePage();
	}

	try {
		_memory->loadRam();
	} catch(Exception_FileCannotOpen e) {
		welcomeStringVector.push_back(e.getString());
	} catch(Exception_CorruptedFile e) {
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
	size_t size = (sizeof(MESSAGE_WELCOME_SCREEN)/sizeof(*MESSAGE_WELCOME_SCREEN));
	vector<string> welcomeList(MESSAGE_WELCOME_SCREEN, MESSAGE_WELCOME_SCREEN+size);

	resizeWindow(DISPLAY_DEFAULT_WIDTH, DISPLAY_DEFAULT_LENGTH);
	printList(welcomeList);
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
	changeListColour(COLOUR_CATEGORY);
	showToUser(message);
	changeListColour(COLOUR_DEFAULT);
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
		taskListType = new ViewType0(_taskList , currentDate);
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
		taskListType = new ViewType1(_taskList, currentDate);
		break;
	case 2:
		taskListType = new ViewType2(_taskList, currentDate);
		break;
	case 3:
		taskListType = new ViewType3(_taskList, currentDate);
		break;
	default:
		taskListType = new ViewType0(_taskList, currentDate);
		break;
	}

	changeListColour(COLOUR_SEARCH);
	printList(createDisplayBox(taskListType->createSearchList()));
	//changeListColour(COLOUR_DEFAULT);

	delete taskListType;
}

void UserInterface::printHelpList(int currentDate, int viewType) {
	size_t size = (sizeof(MESSAGE_HELP_TIPS)/sizeof(*MESSAGE_HELP_TIPS));
	vector<string> helpList(MESSAGE_HELP_TIPS, MESSAGE_HELP_TIPS+size);
	COORD c;

	c.X = DISPLAY_WIDTH;
	c.Y = helpList.size();
	SetConsoleScreenBufferSize(GetStdHandle( STD_OUTPUT_HANDLE), c);

	changeListColour(COLOUR_HELP);
	printList(helpList);

	scrollByAbsoluteCoord(124);
	keyboardCommandScroll();

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

	setDisplayBoxLength(displayList.size());

	messageBox.assign(DISPLAY_WIDTH, MESSAGE_BOX_CHARACTER);
	messageBox.pop_back();

	displayList.insert(displayList.begin(), messageBox);
	displayList.insert(displayList.begin(), MESSAGE_VOID_STRING);
	displayListIter = displayList.begin();
	displayListIter++;

	while(displayList.size() < DISPLAY_BOX_LENGTH) {
		displayList.push_back(MESSAGE_VOID_STRING);
	}
	displayList.insert(displayList.end(), messageBox);

	c.X = DISPLAY_WIDTH;
	c.Y = (displayList.size()+ 4);
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

void UserInterface::setDisplayBoxLength(int size) {
	DISPLAY_BOX_WIDTH = DISPLAY_WIDTH - DISPLAY_SYNC_WIDTH;
	DISPLAY_BOX_LENGTH = size - DISPLAY_SYNC_LENGTH;
	_memory->changeWindowSize(DISPLAY_WIDTH, DISPLAY_LENGTH);
}

void UserInterface::resizeWindow(int width, int length) {
	sprintf_s(buffer, SYSTEM_MODE_CON.c_str(), width, length);
	system(buffer);
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
			setConsoleColor(BLACK, GREY);
			return;
		} else {
			if(colourCoding == COLOUR_SEARCH) {
				setConsoleColor(BLACK, LIGHT_AQUA);
				return;
			} else {
				if(colourCoding == COLOUR_HELP) {
					setConsoleColor(BLACK, LIGHT_YELLOW);
					return;
				} else {
					if(colourCoding == COLOUR_CATEGORY) {
						setConsoleColor(BLACK, LIGHT_AQUA);
						return;
					} else {
						if(colourCoding == COLOUR_FEEDBACK) {
							setConsoleColor(BLACK, LIGHT_AQUA);
						} else {
							setConsoleColorDefault();
						}
					}
				}
			}
		}
	}
}

void UserInterface::setConsoleColor(int background, int foreground) {
	HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int colour = background * 16 + foreground;
	SetConsoleTextAttribute(hConsole, colour);
}

void UserInterface::setConsoleColorDefault() {
	setConsoleColor(BLACK, LIGHT_WHITE);
}

/****************************************************************/

void UserInterface::scrollByAbsoluteCoord(int iRows) {
	HANDLE hStdout;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo; 
	SMALL_RECT srctWindow; 

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hStdout, &csbiInfo);
	srctWindow = csbiInfo.srWindow; 

	if (srctWindow.Top == 124 && iRows == -1) {
		return;
	} 

	if ( srctWindow.Top >= iRows ) { 
		srctWindow.Top -= (SHORT)iRows;
		srctWindow.Bottom -= (SHORT)iRows;
	}

	SetConsoleWindowInfo(hStdout, TRUE, &srctWindow);
}

void UserInterface::keyboardCommandScroll() {
	int keyPress;
	do {
		keyPress = _getch();
		switch(keyPress) {
		case 72:
			scrollByAbsoluteCoord(1);
			break;
		case 80:
			scrollByAbsoluteCoord(-1);
			break;
		case 73:
			scrollByAbsoluteCoord(1);
			scrollByAbsoluteCoord(1);
			scrollByAbsoluteCoord(1);
			scrollByAbsoluteCoord(1);
			scrollByAbsoluteCoord(1);
			scrollByAbsoluteCoord(1);
			break;
		case 81:
			scrollByAbsoluteCoord(-1);
			scrollByAbsoluteCoord(-1);
			scrollByAbsoluteCoord(-1);
			scrollByAbsoluteCoord(-1);
			scrollByAbsoluteCoord(-1);
			scrollByAbsoluteCoord(-1);
			break;
		}
	} while(notExitKey(keyPress));

}

bool UserInterface::notExitKey(int keyPress) {
	if(keyPress == 224
		|| keyPress == 72
		|| keyPress == 224
		|| keyPress == 80
		|| keyPress == 224
		|| keyPress == 75
		|| keyPress == 224
		|| keyPress == 77
		|| keyPress == 224
		|| keyPress == 73
		|| keyPress == 224
		|| keyPress == 81
		|| keyPress == 224
		|| keyPress == 71
		|| keyPress == 224
		|| keyPress == 79
		|| keyPress == 224
		|| keyPress == 82
		|| keyPress == 224
		|| keyPress == 83) {
			return true;
	}	
	return false;
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


