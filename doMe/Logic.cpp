#include "Logic.h"

const string Logic::EXIT_COMMAND = "exit"; 
const string Logic::LIST_DIVIDER = "__________";

Logic::Logic() {
	_settings = new Settings();
	_UI = new UserInterface();
//	_storage = new Storage();
	_taskList = new list<Task*>;
	_prevTaskList = new list<Task*>;
	_searchTaskList = new list<Task*>;
}
void Logic::setEnvironment() {
//	vectorToTaskList(_storage->retrieveData());
	_settings->loadSettings();
}
void Logic::displayWelcomeMessage() {
	_UI->printNotificationWelcome();
	//cout << "Welcome" << endl;
}
void Logic::executeCommandsUntilExitCommand() {
	string command;

	display();

	do {
		_UI->printPromptCommand();
		//cout << "command: ";
		getline(cin, command);
		executeCommand(command);	
	} while (command != EXIT_COMMAND);
}

void Logic::executeSearchCommandsUntilExitCommand(string searchTerm) {
	string command;

	displaySearchList(searchTerm);

	do {
		getline(cin, command);
		executeSearchCommand(command, searchTerm);
	}while(command != EXIT_COMMAND);
}

void Logic::executeCommand(string command) {
	Parser* parser = new Parser(command);
	parser->parse();
	CommandPackage* commandPackage = parser->getCommandPackage();
	COMMAND_TYPE commandType = commandPackage->getCommandType();

	switch(commandType) {
	case ADD:
		add(commandPackage->getTask());
		break;
	case DISPLAY:
		display();
		break;
	case DELETE:
		del(commandPackage->getIndex(), _taskList);
		break;
	case EDIT:
		edit(commandPackage->getIndex(), commandPackage->getTask(), _taskList);
		break;
	case CLEAR:
		clear(_taskList,"lol");
		break;
	case UNDO:
		undo();
		break;
	case SORT:
		sort();
		break;
	case SEARCH:
		search(commandPackage->getDescription());
		break;
	case VIEWTYPE:
		changeViewType(commandPackage->getIndex());
		break;
	case SAVEDIRECTORY:
		changeSaveDirectory(commandPackage->getDescription());
		break;
	case EXIT:
		break;
	default:
		_UI->printNotificationInvalidCommand();
		break;
	}

	//delete parser;
	//delete commandPackage;
}

void Logic::executeSearchCommand(string command, string searchTerm) {
	Parser* parser = new Parser(command);
	parser->parse();
	CommandPackage* commandPackage = parser->getCommandPackage();
	COMMAND_TYPE commandType = commandPackage->getCommandType();

	switch(commandType) {
	case DELETE:
		del(commandPackage->getIndex(), _searchTaskList);
		break;
	case EDIT:	
		edit(commandPackage->getIndex(), commandPackage->getTask(), _searchTaskList);
		break;
	case CLEAR:
		clear(_searchTaskList, searchTerm);
		break;
	case UNDO:
		undo();
		break;
	case EXIT:
		break;
	default:
		_UI->printNotificationInvalidCommand();
		break;
	}

	delete parser;
	//delete commandPackage;
}

void Logic::add(Task* task) {
	if(task == NULL) {
		_UI->printNotificationInvalidAdd();
		return;
	}

	saveLastChange();

	_taskList->push_back(task);
	_UI->printNotificationAdd(task); //some error here (parser + UI issue)

	sort();
	display();
}

void Logic::display(){
	_UI->printTaskList(_taskList, getCurrentDate(), _settings->getViewType()); 
    //error due to logic gave UI invalid task list + current date
    /*
int i = 1;
 for(list<Task*>::iterator iter = _taskList->begin(); iter != _taskList->end(); iter++) {
		cout << i++ << ". "
		<< (*iter)->getName() << " "
		<< (*iter)->getDate1() << " "
		<< (*iter)->getDate2() << " "
		<< (*iter)->getTime1() << " "
		<< (*iter)->getTime2() << " "
		<< (*iter)->getLocation() << endl;
	}
    */
}

void Logic::displaySearchList(string searchTerm) {
//	_UI->printSearchList(_searchTaskList, searchTerm);
}

void Logic::del(int index, list<Task*>* taskList) {
	if(outOfRange(index, taskList)) {
		_UI->printNotificationInvalidDeletion();
		return;
	}

	saveLastChange();

	taskList->erase(indexToListIter(index, taskList));

	display();
}
void Logic::edit(int index, Task* task, list<Task*>* taskList) {
	string name = task->getName();
	int date1 = task->getDate1();
	int date2 = task->getDate2();
	int time1 = task->getTime1();
	int time2 = task->getTime2();
	string location = task->getLocation();

	saveLastChange();

	list<Task*>::iterator iter = indexToListIter(index, taskList);

	if(!name.empty()) {
		(*iter)->setName(name);
	}
	if(date1 != 0) {
		(*iter)->setDate1(date1);
	}
	if(date2 != 0) {
		(*iter)->setDate2(date2);
	}
	if(time1 != 0) {
		(*iter)->setTime1(time1);
	}
	if(time2 != 0) {
		(*iter)->setTime2(time2);
	}
	if(!location.empty()) {
		(*iter)->setLocation(location);
	}

	sort();
	display();
}

void Logic::clear(list<Task*>* taskList, string searchTerm) {
	saveLastChange();

	taskList->clear();

	if(taskList == _taskList) {
		_UI->printNotificationClear();
	}else {
		_UI->printNotificationClearSearch(searchTerm);	
	}
}

void Logic::undo() {
	list<Task*>* tempPtr;

	tempPtr = _taskList;
	_taskList = _prevTaskList;
	_prevTaskList = tempPtr;

	tempPtr = _searchTaskList;
	_searchTaskList = _prevSearchTaskList;
	_prevSearchTaskList = tempPtr;

	display();
}

void Logic::sort() {
//	_taskList->sort(dateSort);
//	_taskList->sort(timeSort);
}

void Logic::search(string searchTerm) {
/*	string command;

	for(list<Task*>::iterator iter = _taskList->begin(); iter != _taskList->end(); iter++) {
		if(foundInTask(*iter, searchTerm)) {
			_searchTaskList->push_back(*iter);
			_taskList->erase(iter);
		}                                                                                                                                                                            
	}

	displaySearchList(searchTerm);
	executeSearchCommandsUntilExitCommand(searchTerm);

	transferBackSearchTasks();

	sort();
	display();*/
}

void Logic::changeViewType(int newViewType) {
	_settings->changeViewType(newViewType);
	_UI->printNotificationViewTypeChange(newViewType);
}

void Logic::changeSaveDirectory(string newSaveDirectory) {
	if(isNotValidDirectory(newSaveDirectory)) {
		_UI->printNotificationInvalidSaveFileDirectory();
		return;
	}

	_settings->changeSaveDirectory(newSaveDirectory);

	_UI->printNotificationChangeSaveFileDirectory(newSaveDirectory);
}

void Logic::saveToTxtFile() {
//	_storage->saveData(taskListToVector(), _settings->getSaveDirectory());
}

void Logic::saveLastChange() {
//	*_prevTaskList = *_taskList;
//	*_prevSearchTaskList = *_searchTaskList;
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

bool Logic::outOfRange(int index, list<Task*>* taskList) {
	if(index > taskList->size() || index < 1) {
		return true;
	}
	return false;
}

bool Logic::dateSort(Task* a, Task* b) {
	return a->getDate1() < b->getDate1();
}

bool Logic::timeSort(Task* a, Task* b) {
	return a->getTime1() < b->getTime2();
}

bool Logic::foundInTask(Task* task, string searchTerm) {
	size_t found = (task->getName()).find(searchTerm);
	if(found != string::npos) {
		return true;
	}
	return false;
}

bool Logic::isNotValidDirectory(string newSaveDirectory) {
	struct stat info;

	if(stat(newSaveDirectory.c_str(), &info) != 0) {
		return true;
	}else if(info.st_mode & S_IFDIR) {
		return false;
	}
	return true;
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

list<Task*>::iterator Logic::indexToListIter(int index, list<Task*>* taskList) {
	list<Task*>::iterator iter = taskList->begin();
	
	for(int i = 1; i < index; i++) {
		iter++;
	}

	return iter;	
}

void Logic::transferBackSearchTasks() {
	while(!_searchTaskList->empty()) {
	_taskList->push_back(_searchTaskList->front());
	_searchTaskList->pop_front();
	}
}