#include "Command.h"
using namespace std;

class Command_Exit : public Command {
public:
	Command_Exit();
	COMMAND_TYPE getCommandType();
};