#include <list>
#include "Task.h"
#include "Command.h"
#include "UserInterface.h"
using namespace std;

class Command_Add : public Command {
private:
	Task* _task;
public:
	Command_Add(list<Task*>* taskList, Task* task);
	int execute();
	int undo();
	Task* getTask();
};