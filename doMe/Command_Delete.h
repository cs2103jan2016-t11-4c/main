#include <list>
#include "Task.h"
#include "Command.h"
#include "UserInterface.h"
using namespace std;

class Command_Delete : public Command {
private:
	int _index;
	Task* _task;

	bool outOfRange();
	list<Task*>::iterator indexToListIter();
public:
	Command_Delete(list<Task*>* taskList, int index);
	int execute();
	int undo();
};