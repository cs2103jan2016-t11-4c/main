//@@author A0125290M
#include "RAM.h"

const string RAM::LIST_DIVIDER = "__________";
const string RAM::DEFAULT_TEXT_FILE_NAME = "doMe.txt";
const string RAM::SPACE = " ";
const string RAM::DONESTATUS_DONE = "*done";
const string RAM::DONESTATUS_UNDONE = "*undone";

void RAM::loadRAM() {
	loadData();
}

void RAM::saveRAM() {
	saveData();
}

void RAM::ramAdd(Task* task) {
	_taskList.push_back(task);
	_lastAddedTask = task;
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

Task* RAM::ramDel(int index) {
	//if(index == LAST_ADDED_INDEX) {
	if(index == 0) {
		//return deleteLastAddedTask();
		Task* lastAddedTask = _lastAddedTask;
		if(lastAddedTask == NULL) {
			return NULL;
		}
		ramDel(lastAddedTask);
		_lastAddedTask = NULL;

		return lastAddedTask;
	}

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

void RAM::ramInsert(list<Task*> oldTaskList) {
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

Task* RAM::ramGetTask(int index) {
	if(index == 0) {
		_lastModifiedTask = _lastAddedTask;
	}else {
		_lastModifiedTask = indexToTask(index);	
	}

	return _lastModifiedTask;
}

Task* RAM::ramGetLastModifiedTask() {
	Task* lastModifiedTask = _lastModifiedTask;

	_lastModifiedTask = NULL;

	return lastModifiedTask;
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
	_taskList.sort([&](Task* a, Task* b) {return convertToLowerCase(a->getName()) < convertToLowerCase(b->getName());});
	_taskList.sort([](Task* a, Task* b) {return a->getTime2() < b->getTime2();});
	_taskList.sort([](Task* a, Task* b) {return a->getDate2() < b->getDate2();});
	_taskList.sort([](Task* a, Task* b) {return a->getDoneStatus() > b->getDoneStatus();});
}

void RAM::loadData() {
	try {
		ramLoadVector(_storage->retrieveData(_settings->getSaveDirectory() + DEFAULT_TEXT_FILE_NAME));
	}catch(Exception_FileCannotOpen e) {
		saveData();
		throw e;
	}
	//	catch(Exception_CorruptedFile e) {
	//		saveData();
	//		throw e;
	//	}
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
		updatedData.push_back(integerToString((*iter)->getDoneStatus()));
		updatedData.push_back(LIST_DIVIDER);
	}
	for(list<Task*>::iterator iter = _tempTaskList.begin(); iter != _tempTaskList.end(); iter++) {
		updatedData.push_back((*iter)->getName());
		updatedData.push_back(integerToString((*iter)->getDate1()));
		updatedData.push_back(integerToString((*iter)->getDate2()));
		updatedData.push_back(integerToString((*iter)->getTime1()));
		updatedData.push_back(integerToString((*iter)->getTime2()));
		updatedData.push_back((*iter)->getLocation());
		updatedData.push_back(integerToString((*iter)->getDoneStatus()));
		updatedData.push_back(LIST_DIVIDER);
	}
	return updatedData;
}

void RAM::ramLoadVector(vector<string>& existingData) {
	if(existingData.size() % 8 != 0) {
		return;
		//		Exception_CorruptedFile e();
		//		throw e;
	}

	for(unsigned int i = 0; i < existingData.size(); i+=8) {
		string name = existingData[i];
		int date1 = stringToInteger(existingData[i+1]);
		int date2 = stringToInteger(existingData[i+2]);
		int time1 = stringToInteger(existingData[i+3]);
		int time2 = stringToInteger(existingData[i+4]);
		string location = existingData[i+5];
		int doneStatus = stringToInteger(existingData[i+6]);

		_taskList.push_back(new Task(name, date1, date2, time1, time2, location, doneStatus));
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
	vector<string> searchTokenList;
	createSearchTokenList(searchTerm, searchTokenList);

	string name = convertToLowerCase(task->getName());
	string location = convertToLowerCase(task->getLocation());
	string date1 = to_string(task->getDate1());
	string date2 = to_string(task->getDate2());
	string time1 = to_string(task->getTime1());
	string time2 = to_string(task->getTime2());
	string doneStatus = getDoneStatusString(task->getDoneStatus());

	string searchString = SPACE + name + SPACE + location + SPACE + date1 + SPACE + date2 + SPACE + time1 + SPACE + time2 + SPACE + doneStatus;	

	for(unsigned int i = 0; i < searchTokenList.size(); i++) {
		size_t found = searchString.find(searchTokenList[i]);
		if(found == string::npos) {
			return false;
		}
	}
	return true;
}

void RAM::createSearchTokenList(string searchTerm, vector<string>& searchTokenList) {
	istringstream is(searchTerm);

	string token;
	while(is >> token) {
		token.insert(0, " ");				//Insert a space at the start
		searchTokenList.push_back(token);
	}
}

string RAM::getDoneStatusString(int doneStatus) {
	if(doneStatus == 1) {
		return "DONESTATUS_DONE";
	}
	return "DONESTATUS_UNDONE";
}

string RAM::convertToLowerCase(string sentence) {
	locale loc;

	for (unsigned int i = 0; i < sentence.size(); ++i) {
		sentence[i] = tolower(sentence[i],loc);
	}

	return sentence;
}

/**********************************************************************/

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
	_lastAddedTask = NULL;
	_lastModifiedTask = NULL;
	_storage = Storage::getInstance();
	_settings = Settings::getInstance();
}