//@@author Joan

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
    void loadSettings();
	bool changeSaveDirectory(string);
	bool changeViewType(int);
    void changeWindowSize(int width,int length);
	string getSaveDirectory(); 
	int getViewType(); 
    string getTextFileName();
    void getWindowSize(int& width, int& length);

	//accessing RAM class object
    void loadRam();
	void saveRam();
	void ramAdd(Task* task);
	void ramDel(Task* task);
	Task* ramDel(int index);
	list<Task*> ramClear();
	void ramInsert(list<Task*>& oldTaskList);
	int ramGetSize();
	Task* ramGetTask(int index);
	Task* ramGetLastModifiedTask();
	bool ramGetSearchState();
	bool ramSearch(string searchTerm);
	string ramUnsearch();
	list<Task*>* ramGetTaskList();
	void ramSort();
};
