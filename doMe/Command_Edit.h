//@@author A0125290M
#include "Command.h"
using namespace std;

class Command_Edit : public Command {
private:
	Task* _task;
	int _index;
	string _newName;
	int _newDate1;
	int _newDate2;
	int _newTime1;
	int _newTime2;
	string _newLocation;
//	int _newDoneStatus;

	string _oldName;
	int _oldDate1;
	int _oldDate2;
	int _oldTime1;
	int _oldTime2;
	string _oldLocation;
//	int _oldDoneStatus;

	bool outOfRange();
public:
	Command_Edit(int index, Task* task);
	bool execute();
	bool undo();
	Task* getTask();
	COMMAND_TYPE getCommandType();
};