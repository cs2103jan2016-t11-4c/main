#pragma once
#include <list>
#include "Memory.h"
#include "Task.h"
using namespace std;

enum COMMAND_TYPE { ADD, DISPLAY, DEL, EDIT, CLEAR, UNDO, SORT, SEARCH, ENDSEARCH, VIEWTYPE, SAVEDIRECTORY, EXIT, INVALID};

class Command {
protected:
	Memory* _memory;
public:
	Command(Memory* memory);
	virtual bool execute() {return false;}
	virtual bool undo() {return false;}
	virtual COMMAND_TYPE getCommandType() {return INVALID;}
	virtual Task* getTask() {return NULL;}
	virtual int getIndex() {return 0;}
	virtual string getDescription() {return "";}
};