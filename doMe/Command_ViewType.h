#include "Command.h"
using namespace std;

class Command_ViewType : public Command {
private:
	int _oldViewType;
	int _newViewType;
public:
	Command_ViewType(Memory* memory, int newViewType);
	bool execute();
	bool undo();
	int getViewType();
	COMMAND_TYPE getCommandType();
};