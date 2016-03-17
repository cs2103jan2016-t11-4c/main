#include "Memory.h"

const string Memory::MESSAGE_VOID_STRING = "";
const string Memory::DEFAULT_TEXT_FILE_NAME = "doMe.txt";
const string Memory::LIST_DIVIDER = "__________";

Memory::Memory(void) {
    _settings = new Settings();
    _storage = new Storage();
}

Memory::~Memory(void) {
    delete _settings;
    delete _storage;
}

/****************************************************************/

bool Memory::loadSettings() {
    return _settings->loadSettings();
}

void Memory::saveSettings() {
    _settings->saveSettings();
}

/****************************************************************/

bool Memory::changeViewType(int viewType) {
    return _settings->changeViewType(viewType);
}

bool Memory::changeSaveDirectory(string saveDirectory) {
    _settings->changeSaveDirectory(saveDirectory);
    return true;
}

/****************************************************************/

bool Memory::getExistingData() {
    vector<string> stringData;

    if(_storage->retrieveData(stringData, _settings->getSaveDirectory())) {
    return false;
    } else {
    vectorToTaskList(stringData);
    return true;
    }

    return true; //tem
}

bool Memory::saveUpdatedData() {
    vector<string> stringData;
    stringData = taskListToVector();
    return _storage->saveData(stringData, _settings->getSaveDirectory());
}

void Memory::vectorToTaskList(vector<string>& existingData) {
    for(unsigned int i = 0; i < existingData.size(); i+=7) {
        string name = existingData[i];
        int date1 = stringToInteger(existingData[i+1]);
        int date2 = stringToInteger(existingData[i+2]);
        int time1 = stringToInteger(existingData[i+3]);
        int time2 = stringToInteger(existingData[i+4]);
        string location = existingData[i+5];

        _taskList->push_back(new Task(name, date1, date2, time1, time2, location));
    }
}

vector<string> Memory::taskListToVector() {
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

string Memory::integerToString(int integer) {
    ostringstream word;
    word << integer;
    return word.str();
}

int Memory::stringToInteger(string text) {
    stringstream ss(text);
    int integer;

    ss >> integer;

    return integer;
}

/****************************************************************/

string Memory::getTextFileName() {
    return _settings->getTextFileName();
}

int Memory::getViewType() {
    return _settings->getViewType();
}

string Memory::getSaveDirectory() {
    return _settings->getSaveDirectory();
}

list<Task*>* Memory::getTaskList() {
    return _taskList;
}

void Memory::ramAddToRawTaskHeap(Task task) {
	_ram->AddToRawTaskHeap(task);
}

void Memory::ramAdd(Task* task) {
	_ram->ramAdd(task);
}

void Memory::ramDel(Task* task) {
	_ram->ramDel(task);
}

Task* Memory::ramDel(int index) {
	return _ram->ramDel(index);
}

void Memory::ramClear() {
	_ram->ramClear();
}

void Memory::ramInsert(list<Task*>& oldTaskList) {
	_ram->ramInsert(oldTaskList);
}

int Memory::ramGetSize() {
	return _ram->ramGetSize();
}

Task* Memory::ramGetTask(int index) {
	return _ram->ramGetTask(index);
}

bool Memory::ramSearch(string searchTerm) {
	return _ram->ramSearch(searchTerm);
}

string Memory::ramUnsearch() {
	return _ram->ramUnsearch();
}

vector<string> Memory::ramGetVector() {
	return _ram->ramGetVector();
}

void Memory::ramLoadVector(vector<string>& existingData) {
	_ram->ramLoadVector(existingData);
}

