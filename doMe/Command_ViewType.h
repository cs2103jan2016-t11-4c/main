#include <list>
#include "Task.h"
#include "Command.h"
#include "Settings.h"
#include "UserInterface.h"
using namespace std;

class Command_ViewType : public Command {
private:
	int _oldViewType;
	int _newViewType;
	Settings* _settings;
public:
	Command_ViewType(Settings* settings, int newViewType);
	void execute();
	void undo();
};