//@@author A0125290M
#include "Command.h"
using namespace std;

class Command_Invalid : public Command {
public:
	Command_Invalid();
	COMMAND_TYPE getCommandType();
	bool execute();
};