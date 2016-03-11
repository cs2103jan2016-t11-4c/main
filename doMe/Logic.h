#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <ctime>
#include <assert.h>
#include <conio.h>
#include "RAM.h"
#include "Task.h"
#include "Parser.h"
#include "Storage.h"
#include "Settings.h"
//#include "TimeCommons.h"
#include "UserInterface.h"
#include "CommandPackage.h"
#include "Command.h"
#include "Command_Add.h"
#include "Command_Delete.h"
#include "Command_Edit.h"
#include "Command_Clear.h"
#include "Command_ViewType.h"
#include "Command_SaveDirectory.h"
#include "Command_Search.h"
using namespace std;

class Logic { 
private:
	RAM* _ram;
	UserInterface* _UI;
	Storage* _storage;
	Settings* _settings;
	stack<Command*>* _commandHistoryList;

	COMMAND_TYPE executeCommand(string commandText);
	void undo();

	void display();
	void displaySuccessfulCommandNotification(COMMAND_TYPE commandType, Command* command);
	void displayInvalidCommandNotification(COMMAND_TYPE commandType, Command* command);

	void saveToTxtFile();
	int stringToInteger(string text);
	int getCurrentDate();

public:
	Logic();
	void setEnvironment();
	void displayWelcomeMessage();
	void executeCommandsUntilExitCommand();
};