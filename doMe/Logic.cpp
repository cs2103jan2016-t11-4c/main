#include "Logic.h"

Logic::Logic() {
	_settings = new Settings();
	_UI = new UserInterface();
	_storage = new Storage();
	_taskList = new vector<Task*>;
	_prevTaskList = new vector<Task*>;
	_searchTaskList = new vector<Task*>;
	_searchMappingTable = new vector<int>;
}
void Logic::setEnvironment() {
	vectorToTaskList(_storage->getExistingData());
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
	} while (command != "exit");
}

/*void Logic::executeSearchCommandsUntilExitCommand(string searchTerm) {
	string command;

	displaySearchList(searchTerm);

	do {
		getline(cin, command);
		executeSearchCommand(command);
	}while(command != "exit");
}*/

void Logic::add(Task* task) {
	if(task == NULL) {
		_UI->printNotificationInvalidAdd();
		return;
	}

	saveLastChange();

	_taskList->push_back(task);
	_UI->printNotificationAdd(task);

	sort();
	display();
}

void Logic::display(){
	_UI->printTaskList(_taskList, getCurrentDate(), _settings->getViewType());	
}

void Logic::displaySearchList(string searchTerm) {
	_UI->printSearchList(_searchTaskList, searchTerm);
}

void Logic::del(int index) {
	if(outOfRange(index)) {
		_UI->printNotificationInvalidDeletion();
		return;
	}

	saveLastChange();

	index--;
	_taskList->erase(_taskList->begin() + index);

	display();
}
void Logic::edit(int index, Task* task) {
	string name = task->getName();
	int date1 = task->getDate1();
	int date2 = task->getDate2();
	int time1 = task->getTime1();
	int time2 = task->getTime2();
	string location = task->getLocation();

	saveLastChange();

	index--;

	if(!name.empty()) {
		(*_taskList)[index]->setName(name);
	}
	if(date1 != 0) {
		(*_taskList)[index]->setDate1(date1);
	}
	if(date2 != 0) {
		(*_taskList)[index]->setDate2(date2);
	}
	if(time1 != 0) {
		(*_taskList)[index]->setTime1(time1);
	}
	if(time2 != 0) {
		(*_taskList)[index]->setTime2(time2);
	}
	if(!location.empty()) {
		(*_taskList)[index]->setLocation(location);
	}

	sort();
	display();
}

void Logic::clear() {
	saveLastChange();

	_taskList->clear();
	_UI->printNotificationClear();
}

void Logic::clearSearchList() {
	saveLastChange();

	for(int i = _searchMappingTable->size() - 1; i >= 0; i--) {
		del((*_searchMappingTable)[i] + 1);
	}
}

void Logic::undo() {
//	if(_prevTaskList->empty()) {
//		cout << "No more undos!" << endl;
//		return;
//	}
	vector<Task*>* tempPtr;

	tempPtr = _taskList;
	_taskList = _prevTaskList;
	_prevTaskList = tempPtr;

//	_prevTaskList->clear();

	display();
}

void Logic::sort() {
	stable_sort(_taskList->begin(), _taskList->end(), dateSort);
	stable_sort(_taskList->begin(), _taskList->end(), timeSort);
}

void Logic::search(string searchTerm) {
	string command;

	for(int i = 0; i < _taskList->size(); i++) {
		if(foundInTask((*_taskList)[i], searchTerm)) {
			_searchTaskList->push_back((*_taskList)[i]);
			_searchMappingTable->push_back(i);
		}                                                                                                                                                                            
	}

	displaySearchList(searchTerm);

	_UI->printPromptCommand();
	getline(cin, command);
	executeSearchCommand(command);

	_searchTaskList->clear();
	_searchMappingTable->clear();
	sort();
	display();
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
	_storage->saveUpdatedData(taskListToVector(), _settings->getSaveDirectory());
}

void Logic::saveLastChange() {
	*_prevTaskList = *_taskList;
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
		del(commandPackage->getIndex());
		break;
	case EDIT:
		edit(commandPackage->getIndex(), commandPackage->getTask());
		break;
	case CLEAR:
		clear();
		break;
	case UNDO:
		undo();
		break;
	case SORT:
		sort();
		break;
	case SEARCH:
		search(commandPackage->getSearchTerm());
		break;
	case VIEWTYPE:
		changeViewType(commandPackage->getViewType());
		break;
	case SAVEDIRECTORY:
		changeSaveDirectory(commandPackage->getSaveDirectory());
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

void Logic::executeSearchCommand(string command) {
	Parser* parser = new Parser(command);
	parser->parse();
	CommandPackage* commandPackage = parser->getCommandPackage();
	COMMAND_TYPE commandType = commandPackage->getCommandType();

	switch(commandType) {
	case DELETE:
		del(getSearchIndex(commandPackage));
		break;
	case EDIT:	
		edit(getSearchIndex(commandPackage), commandPackage->getTask());
		break;
	case CLEAR:
		clearSearchList();
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

	for(int i = 0; i < _taskList->size(); i++) {
		updatedData.push_back((*_taskList)[i]->getName());
		updatedData.push_back(integerToString((*_taskList)[i]->getDate1()));
		updatedData.push_back(integerToString((*_taskList)[i]->getDate2()));
		updatedData.push_back(integerToString((*_taskList)[i]->getTime1()));
		updatedData.push_back(integerToString((*_taskList)[i]->getTime2()));
		updatedData.push_back((*_taskList)[i]->getLocation());
		updatedData.push_back("__________");
	}

	return updatedData;
}

bool Logic::outOfRange(int index) {
	if(index > _taskList->size() || index < 1) {
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

int Logic::getSearchIndex(CommandPackage* commandPackage) {
	int searchIndex;

	searchIndex = (*_searchMappingTable)[commandPackage->getIndex() - 1];
	searchIndex++;

	return searchIndex;
}