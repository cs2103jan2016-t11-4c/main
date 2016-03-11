#include "Command.h"
using namespace std;

class Command_Add : public Command {
private:
	Task* _task;
public:
	Command_Add(RAM* ram, Task* task);
	bool execute();
	bool undo();
	Task* getTask();
//	COMMAND_TYPE getCommandType();
};
