//@@author A0125290M
#include "Command.h"
using namespace std;

class Command_Undo : public Command {
	Command_Undo();
	bool execute();
	bool undo();
	COMMAND_TYPE getCommandType();
};