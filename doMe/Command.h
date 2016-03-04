#pragma once
#include <iostream>
#include <list>
#include "Task.h"
#include "UserInterface.h"
using namespace std;

class Command {
protected:
	list<Task*>* _taskList;
	UserInterface* _UI;
public:
	Command(list<Task*>* taskList, UserInterface* UI);
	virtual void execute() = 0;
	virtual void undo() = 0;
};