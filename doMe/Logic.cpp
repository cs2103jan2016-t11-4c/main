#include "Logic.h"

Logic::Logic() {
	_settings = new Settings();
	_UI = new UI();
	_storage = new Storage();
}
void Logic::setEnvironment() {
	vectorToTaskList(_storage->getExistingData());
	_settings->loadSettings();
	changeSaveDirectory(_settings->getSaveDirectory());
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

void Logic::add(string name, int date1, int date2, int time1, int time2, string location) {
	if(name.empty()) {
		_UI->printInvalidAddNotification();
		return;
	}

	_taskList.push_back(new Task(name, date1, date2, time1, time2, location));
	_UI->printAddNotification(name, date1, date2, time1, time2, location);

	sort();
	display();
}

void Logic::display(){
	_UI->printTaskList(_taskList, _settings->getViewType);	
}

void Logic::del(int index) {
	if(outOfRange(index, _taskList.size())) {
		cout << "Invalid deletion!" << endl;
		return;
	}

	index--;
	_taskList.erase(_taskList.begin() + index);

	display();
}
void Logic::edit(int index, string name, int date1, int date2, int time1, int time2, string location) {
	index--;
	if(!name.empty()) {
		_taskList[index]->setName(name);
	}
	if(date1!=0) {
		_taskList[index]->setDate1(date1);
	}
	if(date2!=0) {
		_taskList[index]->setDate2(date2);
	}
	if(time1!=0) {
		_taskList[index]->setTime1(time1);
	}
	if(time2!=0) {
		_taskList[index]->setTime2(time2);
	}
	if(!location.empty()) {
		_taskList[index]->setLocation(location);
	}

	sort();
	display();
}

void Logic::clear() {
	_taskList.clear();
}

void Logic::undo() {
	if(_prevTaskList.empty()) {
		cout << "No more undos!" << endl;
		return;
	}

	_taskList = _prevTaskList;
	_prevTaskList.clear();
}

void Logic::sort() {
	stable_sort(_taskList.begin(), _taskList.end(), dateSort);
	stable_sort(_taskList.begin(), _taskList.end(), timeSort);
}

void Logic::search(string searchTerm) {
	//vector<int> searchMap;

	for(int i = 0; i < _taskList.size(); i++) {
		if(wordFoundInEntry(searchTerm,_taskList[i]->getName())) {
			_UI->printSearchNotification(searchTerm, _taskList[i]);
		}
	}
}

void Logic::changeViewType(int newViewType) {
	_settings->changeViewType(viewType);
}

void Logic::changeSaveDirectory(string newSaveDirectory) {
	if(isNotValidDirectory(newSaveDirectory)) {
		_UI->printInvalidDirectoryNotification();
		return;
	}
	_storage->changeSaveDirectory(newSaveDirectory);
	_settings->changeSaveDirectory(newSaveDirectory);
}

void Logic::saveToTxtFile() {
	_storage->saveData(taskListToVector());
}

void Logic::saveLastChange() {
	_prevTaskList = _Tasklist;
}

void Logic::executeCommand(string command) {
	Parser* parser = new Parser(command);
	COMMAND_TYPE commandType = parser->getCommandType();

	switch(commandType) {
	case ADD:
		add(parser->getName(), parser->getDate1(), parser->getDate2(), parser->getTime1(), parser->getTime2(), parser->getLocation());
		break;
	case DISPLAY:
		display();
		break;
	case DELETE:
		del(parser->getIndex());
		break;
	case EDIT:
		edit(parser->getIndex(), parser->getName(), parser->getDate1(), parser->getDate2(), parser->getTime1(), parser->getTime2(), parser->getLocation());
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
		search(parser->getSearchTerm());
		break;
	case VIEWTYPE:
		changeViewType(parser->getViewType());
		break;
	case SAVEDIRECTORY:
		changeSaveDirectory(parser->getSaveDirectory());
		break;
	case EXIT:
		break;
	default:
		cout << "Invalid Command!" << endl;
		break;
	}

	delete parser;
}

void Logic::vectorToTaskList(vector<string>& existingData) {
	Parser* parser;

	for(int i = 0; i < existingData.size(); i++) {
		parser = new Parser(existingData[i]);

		_taskList.push_back(new Task(parser->getName(), parser->getDate1(), parser->getDate2(), parser->getTime1(), parser->getTime2(), parser->getLocation()));	
		
		delete parser;
	}
	sort();
}

vector<string> Logic::taskListToVector() {
	vector<string> updatedData;

	for(int i = 0; i < _taskList.size(); i++) {
		updatedData.push_back(_taskList[i]->getName());
		updatedData.push_back(_taskList[i]->getDate1());
		updatedData.push_back(_taskList[i]->getDate2());
		updatedData.push_back(_taskList[i]->getTime1());
		updatedData.push_back(_taskList[i]->getTime2());
		updatedData.push_back(_taskList[i]->getLocation());
		updatedData.push_back("__________");			
	}

	return updatedData;
}

int Logic::outOfRange(int index) {
	if(index > _taskList.size() || index < 1) {
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