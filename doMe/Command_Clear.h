#include <list>
#include "Task.h"
#include "Command.h"
#include "UserInterface.h"
using namespace std;

class Command_Clear : public Command {
private:
	list<Task*> _oldTaskList;
public:
	Command_Clear(list<Task*>* taskList, UserInterface* UI);
	void execute();
	void undo();
};