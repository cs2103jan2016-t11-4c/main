#include "Command.h"

Command::Command(list<Task*>* taskList, UserInterface* UI) {
	_taskList = taskList;
	_UI = UI;
}