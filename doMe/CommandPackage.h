#pragma once
#include <string>
#include "Task.h"
using namespace std;

enum COMMAND_TYPE {
		ADD, DISPLAY, DELETE, EDIT, CLEAR, UNDO, SORT, SEARCH, VIEWTYPE, SAVEDIRECTORY, EXIT, INVALID
	};

class CommandPackage {
private:

	COMMAND_TYPE _commandType;
	Task _task;
	int _index;
	string _description;

public:
	CommandPackage(COMMAND_TYPE commandType = INVALID, Task task = Task(), int index = 0, string description = "");
	~CommandPackage(void);

	COMMAND_TYPE getCommandType();
	Task getTask();
	int getIndex();
	string getDescription();

	void setCommandType(COMMAND_TYPE commandType);
	void setTask(Task task);
	void setIndex(int index);
	void setDescription(string description);

};

