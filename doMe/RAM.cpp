//@@author A0125290M
#include "RAM.h"

const string RAM::LIST_DIVIDER = "__________";
const string RAM::DEFAULT_TEXT_FILE_NAME = "doMe.txt";

RAM* RAM::_instance = 0;

RAM* RAM::getInstance() {
	if (_instance == 0) {
		_instance = new RAM;
	}
	return _instance;
}

RAM::RAM() {
	_searchState = false;
	_searchTerm = "";
	_lastModifiedTask = NULL;
	_storage = Storage::getInstance();
	_settings = Settings::getInstance();
}

void RAM::loadRAM() {
	loadData();
}

void RAM::ramAdd(Task* task) {
	_taskList.push_back(task);
	_lastModifiedTask = task;
	ramUnsearch();
	sort();
	saveData();
}

void RAM::ramDel(Task* task) {
	for(list<Task*>::iterator iter = _taskList.begin(); iter != _taskList.end(); iter++) {
		if(*iter == task) {
			_taskList.erase(iter);
			ramUnsearch();
			saveData();
			return;
		}
	}
}

Task* RAM::ramDel(int index) {						//index must be guranteed to be valid
	list<Task*>::iterator deleteIter = indexToTaskListIter(index);
	Task* deletedTaskPtr = *deleteIter;

	_taskList.erase(deleteIter);

	ramUnsearch();

	saveData();

	return deletedTaskPtr;
}

list<Task*> RAM::ramClear() {
	list<Task*> oldTaskList = _taskList;
	_taskList.clear();
	ramUnsearch();
	saveData();

	return oldTaskList;
}

void RAM::ramInsert(list<Task*>& oldTaskList) {
	while(!oldTaskList.empty()) {
		_taskList.push_back(oldTaskList.front());
		oldTaskList.pop_front();
	}
	ramUnsearch();
	sort();

	saveData();
}

int RAM::ramGetSize() {
	return _taskList.size();
}

Task* RAM::ramGetTask(int index) {		//index must be valid
	if(index == 0) {
		return _lastModifiedTask;
	}
	
	_lastModifiedTask = indexToTask(index);
	return _lastModifiedTask;
}

Task* RAM::ramGetLastModifiedTask() {
	return _lastModifiedTask;
}

bool RAM::ramGetSearchState() {
	return _searchState;
}

bool RAM::ramSearch(string& searchTerm) {
	ramUnsearch();

	list<Task*>::iterator iter = _taskList.begin();
	while(iter != _taskList.end()) {
		if(!foundInTask(*iter, searchTerm)) {
			_tempTaskList.push_back(*iter);
			iter = _taskList.erase(iter);
		}else {
			iter++;
		}
	}

	if(_tempTaskList.empty()) {
		return false;
	}
	
	_searchTerm = searchTerm;
	_searchState = true;

	return true;
}

string RAM::ramUnsearch() {
	while(!_tempTaskList.empty()) {
		_taskList.push_back(_tempTaskList.front());
		_tempTaskList.pop_front();
	}
	_searchState = false;
	sort();

	return _searchTerm;
}

list<Task*>* RAM::ramGetTaskList() {
	return &_taskList;
}

void RAM::ramSort() {
	sort();
}

void RAM::sort() {
	_taskList.sort([](Task* a, Task* b) {return a->getTime2() < b->getTime2();});
	_taskList.sort([](Task* a, Task* b) {return a->getDate2() < b->getDate2();});
	//_taskList.sort([](Task* a, Task* b) {return a->getName() < b->getName();});
	//_taskList.sort([](Task* a, Task* b) {return a->getDoneStatus() < b->getDoneStatus();});
}

void RAM::loadData() {
	try {
		ramLoadVector(_storage->retrieveData(_settings->getSaveDirectory() + DEFAULT_TEXT_FILE_NAME));
	}catch(Exception_FileCannotOpen e) {
		saveData();
		throw e;
	}
}

void RAM::saveData() {
	_storage->saveData(ramGetVector() ,_settings->getSaveDirectory() + DEFAULT_TEXT_FILE_NAME);
}

vector<string> RAM::ramGetVector() {
	vector<string> updatedData;

	for(list<Task*>::iterator iter = _taskList.begin(); iter != _taskList.end(); iter++) {
		updatedData.push_back((*iter)->getName());
		updatedData.push_back(integerToString((*iter)->getDate1()));
		updatedData.push_back(integerToString((*iter)->getDate2()));
		updatedData.push_back(integerToString((*iter)->getTime1()));
		updatedData.push_back(integerToString((*iter)->getTime2()));
		updatedData.push_back((*iter)->getLocation());
		updatedData.push_back(LIST_DIVIDER);
	}
	for(list<Task*>::iterator iter = _tempTaskList.begin(); iter != _tempTaskList.end(); iter++) {
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

void RAM::ramLoadVector(vector<string>& existingData) {
	for(unsigned int i = 0; i < existingData.size(); i+=7) {
		string name = existingData[i];
		int date1 = stringToInteger(existingData[i+1]);
		int date2 = stringToInteger(existingData[i+2]);
		int time1 = stringToInteger(existingData[i+3]);
		int time2 = stringToInteger(existingData[i+4]);
		string location = existingData[i+5];

		_taskList.push_back(new Task(name, date1, date2, time1, time2, location));
	}
	sort();
}

string RAM::integerToString(int integer) {
	ostringstream word;
	word << integer;
	return word.str();
}

int RAM::stringToInteger(string& text) {
	stringstream ss(text);
	int integer;

	ss >> integer;

	return integer;
}

Task* RAM::indexToTask(int index) {
	return *(indexToTaskListIter(index));
}

list<Task*>::iterator RAM::indexToTaskListIter(int index) {
	list<Task*>::iterator iter = _taskList.begin();

	for(int i = 1; i < index; i++) {
		iter++;
	}
	return iter;
}

bool RAM::foundInTask(Task* task, string searchTerm) {
	searchTerm = convertToLowerCase(searchTerm);

	string name = convertToLowerCase(task->getName());
	string location = convertToLowerCase(task->getLocation());
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

string RAM::convertToLowerCase(string sentence) {
	locale loc;

	for (unsigned int i = 0; i < sentence.size(); ++i) {
		sentence[i] = tolower(sentence[i],loc);
	}

	return sentence;
}