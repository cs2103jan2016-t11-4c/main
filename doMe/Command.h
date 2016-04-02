//@@author A0125290M
#pragma once
#include <list>
#include <algorithm>
#include "Memory.h"
#include "Task.h"
#include "Exception_InvalidCommand.h"
using namespace std;

class Memory;

enum CommandType { ADD, DISPLAY, DEL, EDIT, CLEAR, UNDO, REDO, SORT, SEARCH, ENDSEARCH, VIEWTYPE, SAVEDIRECTORY, EXIT, HELP, INVALID};

class Command {
protected:
	Memory* _memory;
public:
	Command();
	virtual bool execute() {return false;}
	virtual bool undo() {return false;}
	virtual CommandType getCommandType() {return INVALID;}
	string getCommandTypeStr();

	virtual Task* getTask() {return NULL;}
	virtual int getIndex() {return 0;}
	virtual	string getSearchTerm() {return "";}
	virtual	string getSaveDirectory() {return "";}
	virtual int getViewType() {return 0;}
	virtual string getStringForm() {return "";}

	virtual void setUndoneCommand(Command* command) {}
	virtual Command* getUndoneCommand() {return NULL;}
	virtual void setRedoneCommand(Command* command) {}
	virtual Command* getRedoneCommand() {return NULL;}
};