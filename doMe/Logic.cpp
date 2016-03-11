#include "Logic.h"

Logic::Logic() {
	_ram = new RAM();
	_settings = new Settings();
	_storage = new Storage();
	_commandHistoryList = new stack<Command*>;

	_UI = new UserInterface(&_ram->_taskList);
}

void Logic::setEnvironment() {	
	_UI->printProgramWelcomePage();

	_settings->loadSettings();
	_ram->vectorToTaskList(_storage->retrieveData(_settings->getSaveDirectory()));
	display();
}

void Logic::displayWelcomeMessage() {
	_UI->printNotificationWelcome();
}

void Logic::executeCommandsUntilExitCommand() {
	string command;

	do {
		_UI->printPromptCommand();
		getline(cin, command);

	} while (executeCommand(command) != EXIT);
}

COMMAND_TYPE Logic::executeCommand(string commandText) {
	if(commandText.empty()) {
		display();
		_UI->printNotificationInvalidCommand();
		return INVALID;
	}

	Parser* parser = new Parser(commandText);
	parser->parse();
	CommandPackage* commandPackage = parser->getCommandPackage();
	COMMAND_TYPE commandType = commandPackage->getCommandType();

	Command* command;

	switch(commandType) {
	case ADD:
		command = new Command_Add(_ram, commandPackage->getTask());
		break;
	case DISPLAY:
		break;
	case DEL:
		command = new Command_Delete(_ram, commandPackage->getIndex());
		break;
	case EDIT:
		command = new Command_Edit(_ram, commandPackage->getIndex(), commandPackage->getTask());
		break;
	case CLEAR:
		command = new Command_Clear(_ram);
		break;
	case UNDO:
		undo();
		return commandType;
	case SEARCH:
		command = new Command_Search(_ram, commandPackage->getDescription());
		break;
	case VIEWTYPE:
		command = new Command_ViewType(_settings, commandPackage->getIndex());
		break;
	case SAVEDIRECTORY:
		command = new Command_SaveDirectory(_settings, commandPackage->getDescription());
		break;
	case EXIT:
		if(_ram->_searchState == true) {
			_ram->returnTasksToTaskList();
			display();
			_UI->printNotificationExitSearch();
			return SEARCH;
		}
		return commandType;
	case INVALID:
		display();
		_UI->printNotificationInvalidCommand();
		return commandType;
	default:
		assert(0);
	}

	if(command->execute() == true) {
		if(commandType != SEARCH) {
			_ram->returnTasksToTaskList();
		}
		display();
		displaySuccessfulCommandNotification(commandType, command);
		_commandHistoryList->push(command);
	}else {
		display();
		displayInvalidCommandNotification(commandType, command);
	}
	saveToTxtFile();
	_settings->saveSettings();

	//delete parser;

	return commandType;
}

void Logic::display() {
	if(_ram->_searchState == true) {
		_UI->printSearchList(_ram->_searchTerm, _settings->getViewType());
	}else {
		_UI->printTaskList(getCurrentDate(), _settings->getViewType());
	}	
}

void Logic::displaySuccessfulCommandNotification(COMMAND_TYPE commandType, Command* command) {
	switch(commandType) {
	case ADD:
		_UI->printNotificationAdd(command->getTask(), _settings->getViewType(), _settings->getTextFileName());
		break;
	case DEL:
		_UI->printNotificationDelete(command->getTask(), _settings->getViewType(), _settings->getTextFileName());
		break;
	case EDIT:
		_UI->printNotificationEdit(command->getTask(), _settings->getViewType());
		break;
	case CLEAR:
		_UI->printNotificationClear(_settings->getTextFileName());
		break;
	case SEARCH:
		break;
	case VIEWTYPE:
		_UI->printNotificationViewTypeChange(command->getIndex());
		break;
	case SAVEDIRECTORY:
		_UI->printNotificationChangeSaveFileDirectory(command->getDescription());
		break;
	default:
		assert(0);
		break;
	}
}

void Logic::displayInvalidCommandNotification(COMMAND_TYPE commandType, Command* command) {

	switch(commandType) {
	case ADD:
		_UI->printNotificationInvalidAdd();
		break;
	case DEL:
		_UI->printNotificationInvalidDeletion();
		break;
	case EDIT:
		_UI->printNotificationInvalidEdit();
		break;
	case VIEWTYPE:
		_UI->printNotificationInvalidViewtype();
		break;
	case SAVEDIRECTORY:
		_UI->printNotificationInvalidSaveFileDirectory();
		break;
	default:
		assert(0);
		break;
	}
}

void Logic::undo() {
	if(_commandHistoryList->empty()) {
		display();
		_UI->printNotificationInvalidUndo();
		return;
	}
	_commandHistoryList->top()->undo();
	delete _commandHistoryList->top();		//delete command
	_commandHistoryList->pop();

	saveToTxtFile();
	display();
	_UI->printNotificationUndo();
}

void Logic::saveToTxtFile() {
	_storage->saveData(_ram->taskListToVector(), _settings->getSaveDirectory());
}

int Logic::stringToInteger(string text) {
	stringstream ss(text);
	int integer;

	ss >> integer;

	return integer;
}

int Logic::getCurrentDate() {
	time_t currentTime;
	struct tm *localTime;

	time( &currentTime );                 		// Get the current time
	localTime = localtime( &currentTime );		// Convert the current time to the local time

	int day    = localTime->tm_mday;
	int month  = localTime->tm_mon + 1;
	int year   = localTime->tm_year + 1900;

	int date = day + month * 100 + year * 10000;	//YYYYMMDD

	return date;
}