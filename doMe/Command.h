//@@author A0125290M
#pragma once
#include <list>
#include "Memory.h"
#include "Task.h"
using namespace std;

class Memory;

enum COMMAND_TYPE { ADD, DISPLAY, DEL, EDIT, CLEAR, UNDO, SORT, SEARCH, ENDSEARCH, VIEWTYPE, SAVEDIRECTORY, EXIT, INVALID};

class Command {
protected:
	Memory* _memory;
public:
	Command();
	virtual bool execute() {return false;}
	virtual bool undo() {return false;}
	virtual COMMAND_TYPE getCommandType() {return INVALID;}
	virtual Task* getTask() {return NULL;}
	virtual int getIndex() {return 0;}
	virtual	string getSearchTerm() {return "";}
	virtual	string getSaveDirectory() {return "";}
	virtual string getStringForm() { return "";}
};