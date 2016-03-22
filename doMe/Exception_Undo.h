//@@author A0125290M
#include "Command.h"
using namespace std;

class Exception_Undo {
private:
	Command* _command;
public:
	Exception_Undo(Command* command);
	Command* getCommand();	
};