/* #pragma once
#include <string>
#include "Task.h"
using namespace std;

#define NO_INDEX 0
#define NO_DESCRIPTION ""

enum COMMAND_TYPE {
		ADD, DISPLAY, DEL, EDIT, CLEAR, UNDO, SORT, SEARCH, ENDSEARCH, VIEWTYPE, SAVEDIRECTORY, EXIT, INVALID
	};

class CommandPackage {
private:

	COMMAND_TYPE _commandType;
	Task _task;
	int _index;
	string _description;

public:
	CommandPackage(COMMAND_TYPE commandType = INVALID, Task task = Task(), int index = NO_INDEX, string description = NO_DESCRIPTION);
	~CommandPackage(void);

	COMMAND_TYPE getCommandType();
	//this method is for unittesting purposes
	string getCommandTypeString();
	Task* getTask();
	int getIndex();
	string getDescription();

	void setCommandType(COMMAND_TYPE commandType);
	void setTask(Task task);
	void setIndex(int index);
	void setDescription(string description);

};*/

