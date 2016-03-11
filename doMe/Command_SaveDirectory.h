#include "Command.h"
#include "Settings.h"
#include <sys/types.h>
#include <sys/stat.h>
using namespace std;

class Command_SaveDirectory : public Command {
private:
	string _oldSaveDirectory;
	string _newSaveDirectory;
	Settings* _settings;

	bool isNotValidDirectory();
public:
	Command_SaveDirectory(Settings* settings, string newSaveDirectory);
	bool execute();
	bool undo();
	string getDescription();
//	COMMAND_TYPE getCommandType();
};