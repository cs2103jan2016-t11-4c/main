//@@author A0125290M
#pragma once
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <locale>
#include "Task.h"
#include "Storage.h"
#include "Settings.h"
using namespace std;

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
	Task* _lastAddedTask;
	Task* _lastModifiedTask;

	static const string LIST_DIVIDER;
	static const string DEFAULT_TEXT_FILE_NAME;
	static const string SPACE;
	static const string DONESTATUS_DONE;
	static const string DONESTATUS_UNDONE;

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
	void createSearchTokenList(string searchTerm, vector<string>& searchTokenList);
	string getDoneStatusString(int doneStatus);
	string convertToLowerCase(string sentence);

public:
	static RAM* getInstance();

	void loadRAM();
	void saveRAM();
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