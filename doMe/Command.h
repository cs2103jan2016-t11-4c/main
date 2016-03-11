#pragma once
#include <list>
#include "RAM.h"
#include "Task.h"
using namespace std;

//enum COMMAND_TYPE { ADD, DISPLAY, DEL, EDIT, CLEAR, UNDO, SORT, SEARCH, ENDSEARCH, VIEWTYPE, SAVEDIRECTORY, EXIT, INVALID};

class Command {
protected:
	RAM* _ram;
public:
	Command(RAM* ram);
	virtual bool execute() = 0;
	virtual bool undo() = 0;
	virtual Task* getTask() {return NULL;}
	virtual int getIndex() {return 0;}
	virtual string getDescription() {return "";}
};