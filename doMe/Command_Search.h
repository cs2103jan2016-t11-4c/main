//@@author A0125290M
#include "Command.h"
using namespace std;

class Command_Search : public Command {
private:
	string _searchTerm;
public:
	Command_Search(string searchTerm);
	bool execute();
	bool undo();
	string getSearchTerm();
	COMMAND_TYPE getCommandType();
};