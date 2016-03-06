#include <list>
#include "Task.h"
#include "Command.h"
#include "Settings.h"
#include "UserInterface.h"
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
	int execute();
	int undo();
	string getDescription();
};