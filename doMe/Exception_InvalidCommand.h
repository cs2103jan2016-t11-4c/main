#include "Command.h"
using namespace std;

class Exception_InvalidCommand {
private:
	COMMAND_TYPE _commandType;
public:
	Exception_InvalidCommand(COMMAND_TYPE commandType);
	COMMAND_TYPE getCommandType();	
};