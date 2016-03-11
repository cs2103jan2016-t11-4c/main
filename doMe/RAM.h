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

	string integerToString(int integer);
	int stringToInteger(string text);
	list<Task*>::iterator indexToTaskListIter(int index);
	bool foundInTask(Task* task, string searchTerm);

	static const string LIST_DIVIDER;

public:
	RAM();

//	Task* addToRawTaskHeap(Task task);

	void add(Task* task);
	Task* del(int index);		//delete using index
	bool del(Task* task);		//delete using Task pointer
	list<Task*> clear();
	void insert(list<Task*>& oldTaskList);

	void sort();

	int getSize();
	Task* getTask(int index);	

	bool shiftTasksFromTaskList(string searchTerm);
	void returnTasksToTaskList();

	vector<string> taskListToVector();
	void vectorToTaskList(vector<string>& existingData);
};