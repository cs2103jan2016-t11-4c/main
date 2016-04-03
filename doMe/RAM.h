//@@author A0125290M
#pragma once
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <locale>
#include "Task.h"
#include "Storage.h"
#include "Command.h"
#include "Settings.h"
using namespace std;

class Command;

class RAM {
private:
	RAM();
	static RAM* _instance;

	Settings* _settings;
	Storage* _storage;
	list<Task*> _taskList;
	list<Task*> _tempTaskList;
	bool _searchState;
	string _searchTerm;
	Task* _lastModifiedTask;

	static const string LIST_DIVIDER;
	static const string DEFAULT_TEXT_FILE_NAME;

	void sort();
	void loadData();
	void saveData();
	vector<string> ramGetVector();
	void ramLoadVector(vector<string>& existingData);
	string integerToString(int integer);
	int stringToInteger(string& text);
	Task* indexToTask(int index);
	list<Task*>::iterator indexToTaskListIter(int index);
	bool foundInTask(Task* task, string searchTerm);
	string convertToLowerCase(string sentence);
	
public:
	static RAM* getInstance();

	void loadRAM();
	void ramAdd(Task* task);
	void ramDel(Task* task);
	Task* ramDel(int index);
	list<Task*> ramClear();
	void ramInsert(list<Task*> oldTaskList);
	int ramGetSize();
	Task* ramGetTask(int index);
	Task* ramGetLastModifiedTask();
	bool ramGetSearchState();
	bool ramSearch(string& searchTerm);
	string ramUnsearch();
	list<Task*>* ramGetTaskList();
	void ramSort();
};