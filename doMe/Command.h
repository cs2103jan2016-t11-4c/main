#pragma once
#include <iostream>
#include <list>
#include "Task.h"
#include "UserInterface.h"
using namespace std;

class Command {
protected:
	list<Task*>* _taskList;
public:
	Command(list<Task*>* taskList);
	virtual int execute() = 0;
	virtual int undo() = 0;
};