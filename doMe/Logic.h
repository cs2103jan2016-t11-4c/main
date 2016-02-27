#include <iostream>
#include <string>
#include <vector>
#include <list>
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
using namespace std;

class Logic { 
private:
	list<Task*>* _taskList;
	list<Task*>* _searchTaskList;
	list<Task*>* _prevTaskList;
	list<Task*>* _prevSearchTaskList;
	UserInterface* _UI;
	Storage* _storage;
	Settings* _settings;

	static const string EXIT_COMMAND;
	static const string LIST_DIVIDER;  
public:
	Logic();
	void setEnvironment();
	void displayWelcomeMessage();
	void executeCommandsUntilExitCommand();
	void executeSearchCommandsUntilExitCommand(string searchTerm);

	void add(Task* task);
	void display();
	void displaySearchList(string searchTerm);
	void del(int index, list<Task*>* taskList);
	void edit(int index, Task* task, list<Task*>* taskList);
	void clear(list<Task*>* taskList, string searchTerm);
	void undo();
	void sort();
	void search(string searchTerm);
	void changeViewType(int newViewType);
	void changeSaveDirectory(string newSaveDirectory);
	void saveToTxtFile();
	void saveLastChange();

	void executeCommand(string command);
	void executeSearchCommand(string command, string searchTerm);
	void vectorToTaskList(vector<string>& existingData);
	vector<string> taskListToVector();
	bool outOfRange(int index, list<Task*>* taskList);
	bool dateSort(Task* a, Task* b);
	bool timeSort(Task* a, Task* b);
	bool foundInTask(Task* task, string searchTerm);
	bool isNotValidDirectory(string newSaveDirectory);
	int stringToInteger(string text);
	string integerToString(int integer);
	int getCurrentDate();
	list<Task*>::iterator indexToListIter(int index, list<Task*>* taskList);
	void transferBackSearchTasks();
};