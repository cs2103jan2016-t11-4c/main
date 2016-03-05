#include "Logic.h"

const string Logic::EXIT_COMMAND = "exit"; 
const string Logic::LIST_DIVIDER = "__________";

Logic::Logic() {
	_settings = new Settings();
//	_storage = new Storage();
	_taskList = new list<Task*>;
	_tempTaskList = new list<Task*>;
	_undoCommandList = new stack<Command*>;
	_searchState = false;

	_UI = new UserInterface(_taskList);
}
void Logic::setEnvironment() {
//	vectorToTaskList(_storage->retrieveData(_settings->getSaveDirectory());
	_settings->loadSettings();
}
void Logic::displayWelcomeMessage() {
	_UI->printNotificationWelcome();
}
void Logic::executeCommandsUntilExitCommand() {
	string command;

	display();

	do {
		_UI->printPromptCommand();
		getline(cin, command);
		executeCommand(command);	
	} while (command != EXIT_COMMAND);
}

void Logic::executeCommand(string commandText) {
	if(commandText.empty()) {
		return;
	}

	Parser* parser = new Parser(commandText);
	parser->parse();
	CommandPackage* commandPackage = parser->getCommandPackage();
	COMMAND_TYPE commandType = commandPackage->getCommandType();

	Command* command;

	if(commandText == "exitsearch") {
		endSearch();
		return;
	}

	if(commandText == "search e") {
		search("e");
		return;
	}

	switch(commandType) {
	case ADD:
		command = new Command_Add(_taskList, commandPackage->getTask());
		break;
	case DISPLAY:
		display();
		return;
	case DELETE:
		command = new Command_Delete(_taskList, commandPackage->getIndex());
		break;
	case EDIT:
		command = new Command_Edit(_taskList, commandPackage->getIndex(), commandPackage->getTask());
		break;
	case CLEAR:
		command = new Command_Clear(_taskList);
		break;
	case UNDO:
		undo();
		return;
	case SEARCH:
		search(commandPackage->getDescription());
		return;
	case ENDSEARCH:
		endSearch();
		return;
	case VIEWTYPE:
		command = new Command_ViewType(_settings, commandPackage->getIndex());
		return;
	case SAVEDIRECTORY:
		command = new Command_SaveDirectory(_settings, commandPackage->getDescription());
		return;
	case EXIT:
		return;
	default:
		_UI->printNotificationInvalidCommand();
		return;
	}

	if(command->execute() == true) {
		displaySuccessfulCommandNotification(commandPackage);
		_undoCommandList->push(command);
		
		if(_searchState == true) {
			search(_searchTerm);
		}

		sort();
		display();
	}else {
		displayInvalidCommandNotification(commandPackage);
	}

	//delete parser;
	//delete commandPackage;
}

void Logic::display() {
	if(_searchState == true) {
		_UI->printSearchList(_searchTerm, _settings->getViewType());
	}else {
		_UI->printTaskList(getCurrentDate(), _settings->getViewType());
	}
}

void Logic::displaySuccessfulCommandNotification(CommandPackage* commandPackage) {
	COMMAND_TYPE commandType = commandPackage->getCommandType();

	switch(commandType) {
	case ADD:
		_UI->printNotificationAdd(commandPackage->getTask(), _settings->getViewType(), "doMe.txt");
		break;
	case DELETE:
		cout << "Something was deleted lol" << endl;
		break;
	case EDIT:
		cout << "Something was edited lol" << endl;
		break;
	case CLEAR:
		_UI->printNotificationClear("doMe.txt");
		break;
	case VIEWTYPE:
		_UI->printNotificationViewTypeChange(commandPackage->getIndex());
		break;
	case SAVEDIRECTORY:
		_UI->printNotificationChangeSaveFileDirectory(commandPackage->getDescription());
		break;
	default:
		assert(0);
		break;
	}
}

void Logic::displayInvalidCommandNotification(CommandPackage* commandPackage) {
	COMMAND_TYPE commandType = commandPackage->getCommandType();

	switch(commandType) {
	case ADD:
		_UI->printNotificationInvalidAdd();
		break;
	case DELETE:
		_UI->printNotificationInvalidDeletion();
		break;
	case EDIT:
//		_UI->printNotificationInvalidEdit();
		break;
	case VIEWTYPE:
//		_UI->printNotificationInvalidViewType();
		break;
	case SAVEDIRECTORY:
		_UI->printNotificationInvalidSaveFileDirectory();
		break;
	default:
		assert(0);
		break;
	}
}

void Logic::search(string searchTerm) {
	transferBackSearchTasks();

	list<Task*>::iterator iter = _taskList->begin();
	while(iter != _taskList->end()) {
		if(!foundInTask(*iter, searchTerm)) {
			_tempTaskList->push_back(*iter);
			iter = _taskList->erase(iter);
		}else {
			iter++;
		}
	}

	_searchTerm = searchTerm;
	_searchState = true;
	sort();
	display();
}

void Logic::endSearch() {
	transferBackSearchTasks();
	_searchState = false;

	sort();
	display();
}

void Logic::undo() {
	if(_undoCommandList->empty()) {
//		_UI->printNotificationInvalidUndo();
		cout << "Cannot undo anymore!" <<endl;
		return;
	}
	_undoCommandList->top()->undo();
	delete _undoCommandList->top();
	_undoCommandList->pop();
	sort();
	display();
}

void Logic::sort() {
	_taskList->sort([](Task* a, Task* b) {return a->getDate1() < b->getDate1();});
	_taskList->sort([](Task* a, Task* b) {return a->getTime1() < b->getTime2();});
}

void Logic::saveToTxtFile() {
//	_storage->saveData(taskListToVector(), _settings->getSaveDirectory());
}

void Logic::vectorToTaskList(vector<string>& existingData) {
	for(int i = 0; i < existingData.size(); i+=7) {
		string name = existingData[i];
		int date1 = stringToInteger(existingData[i+1]);
		int date2 = stringToInteger(existingData[i+2]);
		int time1 = stringToInteger(existingData[i+3]);
		int time2 = stringToInteger(existingData[i+4]);
		string location = existingData[i+5];

		_taskList->push_back(new Task(name, date1, date2, time1, time2, location));
	}
	sort();
}

vector<string> Logic::taskListToVector() {
	vector<string> updatedData;

	for(list<Task*>::iterator iter = _taskList->begin(); iter != _taskList->end(); iter++) {
		updatedData.push_back((*iter)->getName());
		updatedData.push_back(integerToString((*iter)->getDate1()));
		updatedData.push_back(integerToString((*iter)->getDate2()));
		updatedData.push_back(integerToString((*iter)->getTime1()));
		updatedData.push_back(integerToString((*iter)->getTime2()));
		updatedData.push_back((*iter)->getLocation());
		updatedData.push_back(LIST_DIVIDER);
	}
	return updatedData;
}

bool Logic::foundInTask(Task* task, string searchTerm) {
	string name = task->getName();
	string location = task->getLocation();
	string date1 = integerToString(task->getDate1());
	string date2 = integerToString(task->getDate2());
	string time1 = integerToString(task->getTime1());
	string time2 = integerToString(task->getTime2());

	size_t found = name.find(searchTerm);
	if(found != string::npos) {
		return true;
	}

	found = location.find(searchTerm);
	if(found != string::npos) {
		return true;
	}

	found = date1.find(searchTerm);
	if(found != string::npos) {
		return true;
	}

	found = date2.find(searchTerm);
	if(found != string::npos) {
		return true;
	}

	found = time1.find(searchTerm);
	if(found != string::npos) {
		return true;
	}

	found = time2.find(searchTerm);
	if(found != string::npos) {
		return true;
	}

	return false;
}

int Logic::stringToInteger(string text) {
	stringstream ss(text);
	int integer;

	ss >> integer;

	return integer;
}

string Logic::integerToString(int integer) {
	ostringstream word;
	word << integer;
	return word.str();
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

void Logic::transferBackSearchTasks() {
	while(!_tempTaskList->empty()) {
	_taskList->push_back(_tempTaskList->front());
	_tempTaskList->pop_front();
	}
}