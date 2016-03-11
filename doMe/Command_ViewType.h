#include "Command.h"
#include "Settings.h"
using namespace std;

class Command_ViewType : public Command {
private:
	int _oldViewType;
	int _newViewType;
	Settings* _settings;
public:
	Command_ViewType(Settings* settings, int newViewType);
	bool execute();
	bool undo();
	int getIndex();
//	COMMAND_TYPE getCommandType();
};