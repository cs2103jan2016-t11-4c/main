#include "UserInterface.h"

const string MESSAGE_FIRST_TIME = "This is your first time using this programme";
const string MESSAGE_SAVE_FILE_NAME = "Input your save file name: ";
const string MESSAGE_SET_SAVE_FILE_DIRECTORY = "New save directory: %s";
const string MESSAGE_SET_SAVE_FILE_DIRECTORY_PROMPT = "Set your save file directory: ";
const string MESSAGE_SET_INVALID_SAVE_FILE_DIRECTORY = "Invalid inputted file directory";
const string MESSAGE_EMPTY_SAVE_FILE_DIRECTORY = "Your file is save at the current directory";
const string MESSAGE_TIP_SAVE_FILE_DIRECTORY = "You can change your directory later";

const string COMMAND_PROMPT = "command: ";
const string EXIT_COMMAND;
const string MESSAGE_WELCOME = "Welcome to doMe. Your %s is ready for use";
const string MESSAGE_ADD = "Added \"%s\" into %s";
const string MESSAGE_INVALID_ADD = "An invalid addition has been inputted. Please try again.";
const string MESSAGE_EMPTY = "Your file \"%s\" is currently empty";
const string MESSAGE_DELETE = "Deleted \"%s\" from %s";
const string MESSAGE_INVALID_DELETE = "An invalid deletion has been inputted. Please try again.";
const string MESSAGE_CLEAR = "cleared %s from %s";
const string MESSAGE_SEARCH = "Searching %s";
const string MESSAGE_DISPLAY_CONTENTS = "%d. %s";

const string ERROR_INVALID_COMMAND_FORMAT = "Invalid command format has been inputted. Please try again";
const string ERROR_INVALID_COMMAND = "Invalid command has been inputted. Please try again";
const string MESSAGE_HELP_TIPS = 
	"add <task description> \n delete <index> \n edit <task description>"; //test ideas?

UserInterface::UserInterface(void) {
}

UserInterface::~UserInterface(void) {
}

void UserInterface::updateTextFileName(string newTextFileName) {
	_textFileName = newTextFileName;
}

void UserInterface::printFirstTimeUserPrompt() {
	showToUser(MESSAGE_FIRST_TIME);
	showToUser(MESSAGE_SAVE_FILE_NAME);
}

void UserInterface::printFirstTimeUserDirectoryPrompt() {
	showToUser(MESSAGE_SET_SAVE_FILE_DIRECTORY_PROMPT);
}

void UserInterface::printInvalidSaveFileDirectory() {
	showToUser(MESSAGE_SET_INVALID_SAVE_FILE_DIRECTORY);
}

void UserInterface::printChangeSaveFileDirectory(string newDirectory) {
	sprintf_s(buffer, MESSAGE_SET_SAVE_FILE_DIRECTORY.c_str(), newDirectory.c_str());
	showToUser(buffer);
}

void UserInterface::printChangeSaveFileDirectory() {
	showToUser(MESSAGE_EMPTY_SAVE_FILE_DIRECTORY);
	showToUser(MESSAGE_TIP_SAVE_FILE_DIRECTORY);
}


void UserInterface::printTaskList(vector<Task*> *taskList, string currentDate ,int viewType) {
	vector<Task*>::iterator taskListIter = (*taskList).begin();
	vector<Task*> displayList;
	int index = 1;
	
	//create display list 
	//not refactored yet for future development to different view type
	while(taskListIter != (*taskList).end()) {
		
		if((**taskListIter).getFirstDate() >= currentDate) {
			displayList.push_back(*taskListIter);
		}
		taskListIter++;
	}
	
	//printing display list
	vector<Task*>::iterator displayListIter = displayList.begin();
	while(displayListIter != displayList.end()) {
		sprintf_s(buffer, MESSAGE_DISPLAY_CONTENTS.c_str(),index , ((**displayListIter).getTaskString()).c_str());
		showToUser(buffer);
		
		index++;
		displayListIter++;
	}
}


void UserInterface::showToUser(string string) {
	cout << string << endl;
}
