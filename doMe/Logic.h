#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
#include <sys/types.h>
#include <sys/stat.h>
#include <sstream>
#include <ctime>
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

	static const string EXIT_COMMAND;
	static const string LIST_DIVIDER;

	void executeCommand(string commandText);
	void search(string searchTerm);
	void endSearch();
	void undo();

	void sort();
	void display();
	void saveToTxtFile();
	void vectorToTaskList(vector<string>& existingData);
	vector<string> taskListToVector();
	bool foundInTask(Task* task, string searchTerm);
	bool isNotValidDirectory(string newSaveDirectory);
	int stringToInteger(string text);
	string integerToString(int integer);
	int getCurrentDate();
	void transferBackSearchTasks();

public:
	Logic();
	void setEnvironment();
	void displayWelcomeMessage();
	void executeCommandsUntilExitCommand();
};