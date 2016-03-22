//@@author A0125290M
#pragma once
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include "Task.h"
#include "Storage.h"
#include "Command.h"
using namespace std;

class RAM {
public: //is this supposed to be private? -joan
	list<Task*> _taskList;
	list<Task*> _tempTaskList;
	bool _searchState;
	string _searchTerm;
	Task* _lastAddedTask;

	void sort();
	void loadData(); //in constructor of RAM
	void saveData();
	vector<string> ramGetVector();
	void ramLoadVector(vector<string>& existingData);
	string integerToString(int integer);
	int stringToInteger(string text);
	list<Task*>::iterator indexToTaskListIter(int index);
	bool foundInTask(Task* task, string searchTerm);

	static const string LIST_DIVIDER;
	static const string DEFAULT_TEXT_FILE_NAME; //unsure about the visibility -joan

public:
	RAM();
	//are ALL these ought to be API of Memory component? -joan
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
	list<Task*>* getTaskList();
};
