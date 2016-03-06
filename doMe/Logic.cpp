#include "Logic.h"

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

	string space = "               ";
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
	cout << space; cout << "           <Press any key to continue>" << endl;

	getch();

	display(); //initial display
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
		command = new Command_Add(_taskList, commandPackage->getTask());
		break;
	case DISPLAY:
		endSearch();
		return commandType;
	case DEL:
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
		return commandType;
	case SEARCH:
		search(commandPackage->getDescription());
		sort();
		display();
		return commandType;
	case VIEWTYPE:
		command = new Command_ViewType(_settings, commandPackage->getIndex());
		return commandType;
	case SAVEDIRECTORY:
		command = new Command_SaveDirectory(_settings, commandPackage->getDescription());
		return commandType;
	case EXIT:
		if(_searchState == true) {
			endSearch();
			_UI->printNotificationExitSearch();
			return DISPLAY;
		}
		return commandType;
	case INVALID:
		display();
		_UI->printNotificationInvalidCommand();
		return commandType;
	default:
		assert(0);
	}

	if(command->execute() == 1) {
		sort();
		display();
		displaySuccessfulCommandNotification(commandType, command);
		_undoCommandList->push(command);

		if(_searchState == true) {
			search(_searchTerm);
		}
	}else {
		display();
		displayInvalidCommandNotification(commandType, command);
	}

	//delete parser;
	//delete commandPackage;

	return commandType;
}

void Logic::display() {
	if(_searchState == true) {
		_UI->printSearchList(_searchTerm, _settings->getViewType());
	}else {
		_UI->printTaskList(getCurrentDate(), _settings->getViewType());
	}	
}

void Logic::displaySuccessfulCommandNotification(COMMAND_TYPE commandType, Command* command) {
	switch(commandType) {
	case ADD:
		_UI->printNotificationAdd(command->getTask(), _settings->getViewType(), "doMe.txt");
		break;
	case DEL:
		_UI->printNotificationDelete(command->getTask(), _settings->getViewType(), "doMe.txt");
		break;
	case EDIT:
		_UI->printNotificationEdit(command->getTask(), _settings->getViewType());
		break;
	case CLEAR:
		_UI->printNotificationClear("doMe.txt");
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
}

void Logic::endSearch() {
	transferBackSearchTasks();
	_searchState = false;

	sort();
	display();
}

void Logic::undo() {
	if(_undoCommandList->empty()) {
		display();
		_UI->printNotificationInvalidUndo();
		return;
	}
	_undoCommandList->top()->undo();
	delete _undoCommandList->top();
	_undoCommandList->pop();
	sort();
	display();
	_UI->printNotificationUndo();
}

void Logic::sort() {
	_taskList->sort([](Task* a, Task* b) {return a->getDate1() < b->getDate1();});
	_taskList->sort([](Task* a, Task* b) {return a->getTime1() < b->getTime1();});
}

void Logic::saveToTxtFile() {
	//	_storage->saveData(taskListToVector(), _settings->getSaveDirectory());
}

void Logic::vectorToTaskList(vector<string>& existingData) {
	for(unsigned int i = 0; i < existingData.size(); i+=7) {
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