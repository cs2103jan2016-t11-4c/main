#include "Memory.h"

Memory* Memory::_instance = NULL;

Memory* Memory::getInstance() {
	if (_instance == NULL) {
		_instance = new Memory;
	}
	return _instance;
}

Memory::Memory() {
	_settings = Settings::getInstance(); //main functionality from Settings constructor
	_ram = RAM::getInstance();			 //main functionality from RAM constructor
}

void Memory::loadSettings() {
    _settings->loadSettings();
}

string Memory::getSaveDirectory() {
	return _settings->getSaveDirectory();
}

string Memory::getTextFileName() {
    return _settings->getTextFileName();
}

int Memory::getViewType() {
    return _settings->getViewType();
}

void Memory::changeSaveDirectory(string newDirectory)
{
	_settings->changeSaveDirectory(newDirectory);
}

bool Memory::changeViewType(int newViewType)
{
	return _settings->changeViewType(newViewType);
}

void Memory::resizeWindow()
{
	_settings->resizeWindow();
}

void Memory::ramAdd(Task* task) {
	_ram->ramAdd(task);
    _settings->saveSettings();
}

void Memory::ramDel(Task* task) {
	_ram->ramDel(task);
    _settings->saveSettings();

}

Task* Memory::ramDel(int index) {
	return _ram->ramDel(index);
    _settings->saveSettings();

}

list<Task*> Memory::ramClear() {
	return _ram->ramClear();
    _settings->saveSettings();

}

void Memory::ramInsert(list<Task*>& oldTaskList) {
	_ram->ramInsert(oldTaskList);
    _settings->saveSettings();

}

int Memory::ramGetSize() {
	return _ram->ramGetSize();

}

Task* Memory::ramGetTask(int index) {
	return _ram->ramGetTask(index);
    _settings->saveSettings();

}

bool Memory::ramGetSearchState() {
	return _ram->ramGetSearchState();
}

bool Memory::ramSearch(string searchTerm) {
	return _ram->ramSearch(searchTerm);
}

string Memory::ramUnsearch() {
	return _ram->ramUnsearch();
}

list<Task*>* Memory::ramGetTaskList() {
	return _ram->ramGetTaskList();
}

void Memory::ramSort() {
	_ram->ramSort();
}