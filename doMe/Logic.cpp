#include "Logic.h"

Logic::Logic() {
	_settings = new Settings();
	_UI = new UserInterface();
	_storage = new Storage();
	_taskList = new vector<Task*>;
	_prevTaskList = new vector<Task*>;
}
void Logic::setEnvironment() {
	vectorToTaskList(_storage->getExistingData());
	_settings->loadSettings();
}
void Logic::displayWelcomeMessage() {
	_UI->printWelcomeMessage();
}
void Logic::executeCommandsUntilExitCommand() {
	string command;

	display();

	do {
		cout << "command: ";
		getline(cin, command);
		executeCommand(command);	
	} while (command != "exit");
}

void Logic::add(Task* task) {
	if(task == NULL) {
		_UI->printInvalidAddNotification();
		return;
	}

	saveLastChange();

	_taskList->push_back(task);
	_UI->printAddNotification(task);

	sort();
	display();
}

void Logic::display(){
	_UI->printTaskList(_taskList, _settings->getViewType());	
}

void Logic::del(int index) {
	if(outOfRange(index, _taskList->size())) {
		cout << "Invalid deletion!" << endl;
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
	_UI->printClearNotification();
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
	//vector<int> searchMap;

	for(int i = 0; i < _taskList->size(); i++) {
		if(wordFoundInEntry(searchTerm,(*_taskList)[i]->getName())) {
			_UI->printSearchNotification(searchTerm, (*_taskList)[i]);
		}
	}
}

void Logic::changeViewType(int newViewType) {
	_settings->changeViewType(newViewType);
	_UI->printViewTypeChangeNotification(newViewType);
}

void Logic::changeSaveDirectory(string newSaveDirectory) {
	if(isNotValidDirectory(newSaveDirectory)) {
		_UI->printInvalidDirectoryNotification();
		return;
	}

	_settings->changeSaveDirectory(newSaveDirectory);

	_UI->printSaveDirectoryChangeNotification(newSaveDirectory);
}

void Logic::saveToTxtFile() {
	_storage->saveUpdatedData(taskListToVector(), _settings->getSaveDirectory());
}

void Logic::saveLastChange() {
	*_prevTaskList = *_tasklist;
}

void Logic::executeCommand(string command) {
	Parser* parser = new Parser(command);
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
		cout << "Invalid Command!" << endl;
		break;
	}

	delete parser;
	//delete commandPackage;
}

void Logic::vectorToTaskList(vector<string>& existingData) {
	for(int i = 0; i < existingData.size(); i+=7) {
		string name = existingData[i];
		int date1 = existingData[i+1];
		int date2 = existingData[i+2];
		int time1 = existingData[i+3];
		int time2 = existingData[i+4];
		string location = existingData[i+5];

		_taskList->push_back(new Task(name, date1, date2, time1, time2, location));
	}
	sort();
}

vector<string> Logic::taskListToVector() {
	vector<string> updatedData;

	for(int i = 0; i < _taskList->size(); i++) {
		updatedData.push_back((*_taskList)[i]->getName());
		updatedData.push_back((*_taskList)[i]->getDate1());
		updatedData.push_back((*_taskList)[i]->getDate2());
		updatedData.push_back((*_taskList)[i]->getTime1());
		updatedData.push_back((*_taskList)[i]->getTime2());
		updatedData.push_back((*_taskList)[i]->getLocation());
		updatedData.push_back("__________");			
	}

	return updatedData;
}

int Logic::outOfRange(int index) {
	if(index > _taskList->size() || index < 1) {
		return 1;
	}
	return 0;
}

bool Logic::dateSort(Task* a, Task* b) {
	return a->getDate1() < b->getDate1();
}

bool Logic::timeSort(Task* a, Task* b) {
	return a->getTime1() < b->getTime2();
}

int Logic::wordFoundInEntry(string text, string entry) {
	size_t found = entry.find(text);
	if(found != string::npos) {
		return 1;
	}
	return 0;
}

int Logic::isNotValidDirectory(string newSaveDirectory) {
	struct stat info;

	if(stat(newSaveDirectory.c_str(), &info) != 0) {
		return 1;
	}else if(info.st_mode & S_IFDIR) {
		return 0;
	}
	return 1;
}