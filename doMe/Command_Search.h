#include "Command.h"
using namespace std;

class Command_Search : public Command {
private:
	string _searchTerm;
public:
	Command_Search(Memory* memory, string searchTerm);
	bool execute();
	bool undo();
	string getSearchTerm();
	COMMAND_TYPE getCommandType();
};