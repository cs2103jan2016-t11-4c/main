#include "Command.h"
using namespace std;

class Command_SaveDirectory : public Command {
private:
	string _oldSaveDirectory;
	string _newSaveDirectory;
public:
	Command_SaveDirectory(Memory* memory, string newSaveDirectory);
	bool execute();
	bool undo();
	string getSaveDirectory();
	COMMAND_TYPE getCommandType();
};