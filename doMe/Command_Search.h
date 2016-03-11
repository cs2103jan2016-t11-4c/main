#include "Task.h"
#include "Command.h"
using namespace std;

class Command_Search : public Command {
private:
	string _searchTerm;
public:
	Command_Search(RAM* ram, string searchTerm);
	bool execute();
	bool undo();
//	COMMAND_TYPE getCommandType();
};