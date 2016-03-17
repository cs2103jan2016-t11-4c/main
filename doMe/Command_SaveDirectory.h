//@@author A0125290M
#include "Command.h"
using namespace std;

class Command_SaveDirectory : public Command {
private:
	string _oldSaveDirectory;
	string _newSaveDirectory;
	int _errorType;
public:
	Command_SaveDirectory(string newSaveDirectory);
	bool execute();
	bool undo();
	string getSaveDirectory();
	int getErrorType();
	COMMAND_TYPE getCommandType();
};