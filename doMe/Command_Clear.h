#include "Command.h"
using namespace std;

class Command_Clear : public Command {
private:
	list<Task*> _oldTaskList;
public:
	Command_Clear(RAM* ram);
	bool execute();
	bool undo();
//	COMMAND_TYPE getCommandType();
};