#include "Memory.h"

Memory* Memory::_instance = 0;

Memory* Memory::getInstance()
{
	if (_instance == 0) {
		_instance = new Memory;
	}
	return _instance;
}

Memory::Memory() 
{
	_settings = Settings::getInstance(); //main functionality from Settings constructor
	_ram = RAM::getInstance();			 //main functionality from RAM constructor
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

Task* Memory::ramAddToRawTaskHeap(Task* task) {
	return _ram->ramAddToRawTaskHeap(task);
}

Command* Memory::ramAddToRawCommandHeap(Command* command) {
	return _ram->ramAddToRawCommandHeap(command);
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

list<Task*> Memory::ramClear() {
	return _ram->ramClear();
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