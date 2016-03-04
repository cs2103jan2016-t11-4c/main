#pragma once
#include <list>
#include "Task.h"
#include "Command.h"
#include "UserInterface.h"
using namespace std;

class Command_Add : public Command {
private:
	Task* _task;
public:
	Command_Add(list<Task*>* taskList, UserInterface* UI, Task* task);
	void execute();
	void undo();
};