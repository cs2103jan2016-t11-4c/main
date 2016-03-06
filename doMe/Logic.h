#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <assert.h>
#include <conio.h>
#include "Task.h"
#include "Parser.h"
#include "Storage.h"
#include "Settings.h"
#include "UserInterface.h"
#include "CommandPackage.h"
#include "Command.h"
#include "Command_Add.h"
#include "Command_Delete.h"
#include "Command_Edit.h"
#include "Command_Clear.h"
#include "Command_ViewType.h"
#include "Command_SaveDirectory.h"
using namespace std;

class Logic { 
private:
	list<Task*>* _taskList;
	list<Task*>* _tempTaskList;
	stack<Command*>* _undoCommandList;
	UserInterface* _UI;
	Storage* _storage;
	Settings* _settings;
	bool _searchState;
	string _searchTerm;

	static const string LIST_DIVIDER;

	COMMAND_TYPE executeCommand(string commandText);
	void search(string searchTerm);
	void endSearch();
	void undo();

	void sort();
	void display();
	void displaySuccessfulCommandNotification(COMMAND_TYPE commandType, Command* command);
	void displayInvalidCommandNotification(COMMAND_TYPE commandType, Command* command);

	void saveToTxtFile();
	void vectorToTaskList(vector<string>& existingData);
	vector<string> taskListToVector();
	int stringToInteger(string text);
	string integerToString(int integer);
	int getCurrentDate();
	bool foundInTask(Task* task, string searchTerm);
	void transferBackSearchTasks();

public:
	Logic();
	void setEnvironment();
	void displayWelcomeMessage();
	void executeCommandsUntilExitCommand();
};