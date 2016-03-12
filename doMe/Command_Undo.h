#include "Command.h"
using namespace std;

class Command_Undo : public Command {
	Command_Undo();
	COMMAND_TYPE getCommandType();
};