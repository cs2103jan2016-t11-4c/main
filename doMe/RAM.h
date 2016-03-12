#pragma once
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include "Task.h"
using namespace std;

class RAM {
public:
	list<Task*> _taskList;
	list<Task*> _tempTaskList;
	vector<Task> _rawTaskHeap;
	bool _searchState;
	string _searchTerm;
	Task* _lastAddedTask;

	void sort();
	string integerToString(int integer);
	int stringToInteger(string text);
	list<Task*>::iterator indexToTaskListIter(int index);
	bool foundInTask(Task* task, string searchTerm);

	static const string LIST_DIVIDER;

public:
	RAM();
	Task* ramAddToRawTaskHeap(Task task);
	void ramAdd(Task* task);
	void ramDel(Task* task);
	Task* ramDel(int index);
	list<Task*> ramClear();
	void ramInsert(list<Task*>& oldTaskList);
	int ramGetSize();
	Task* ramGetTask(int index);
	bool ramSearch(string searchTerm);
	void ramUnsearch();
	vector<string> ramGetVector();
	void ramLoadVector(vector<string>& existingData);
};