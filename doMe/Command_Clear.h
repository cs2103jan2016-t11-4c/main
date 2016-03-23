//@@author A0125290M
#include "Command.h"
using namespace std;

class Command_Clear : public Command {
private:
	list<Task*> _oldTaskList;
	vector<int> _deleteList;
public:
	Command_Clear(vector<int>* deleteList);
	bool execute();
	bool undo();
	COMMAND_TYPE getCommandType();
};