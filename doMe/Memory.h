#pragma once
#include <list>
#include <string>
#include "RAM.h"
#include "Settings.h"

class RAM;
class Command;

class Memory {
private:
	RAM* _ram;
	Settings* _settings;
	
	static Memory* _instance;
	Memory();

public:
	static Memory* getInstance();

	//accessing Settings class object
	void changeSaveDirectory(string);
	bool changeViewType(int);
	void resizeWindow();

	//I need these - Michael
	// if only RAM need these, don't need to be API. RAM calls these fns directly from the singleton Settings object
	// unless other outside classes need these from Memory component
	/* string getSaveDirectory(); 
	int getViewType(); */

	//accessing RAM class object
	Task* ramAddToRawTaskHeap(Task* task);
	Command* ramAddToRawCommandHeap(Command* command);
	void ramAdd(Task* task);
	void ramDel(Task* task);
	Task* ramDel(int index);
	list<Task*> ramClear();
	void ramInsert(list<Task*>& oldTaskList);
	int ramGetSize();
	Task* ramGetTask(int index);
	bool ramGetSearchState();
	bool ramSearch(string searchTerm);
	string ramUnsearch();
	list<Task*>* ramGetTaskList();
	void ramSort();
};
