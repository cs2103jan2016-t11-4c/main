//@@author A0125290M
#include "Command.h"
using namespace std;

class Exception_InvalidCommand {
private:
	Command* _command;
public:
	Exception_InvalidCommand(Command* command);
	Command* getCommand();	
};