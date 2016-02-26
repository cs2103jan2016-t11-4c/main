#include <iostream>
#include <string>
#include <vector>
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
	vector<Task*>* _taskList;
	vector<Task*>* _prevTaskList;
	vector<Task*>* _searchTaskList;
	vector<int>* _searchMappingTable;
	UserInterface* _UI;
	Storage* _storage;
	Settings* _settings;
public:
	Logic();
	void setEnvironment();
	void displayWelcomeMessage();
	void executeCommandsUntilExitCommand();
//	void executeSearchCommandsUntilExitCommand(string searchTerm);		Still Working on this method, for now you can only do one command after search

	void add(Task* task);
	void display();
	void displaySearchList(string searchTerm);
	void del(int index);
	void edit(int index, Task* task);
	void clear();
	void clearSearchList();
	void undo();
	void sort();
	void search(string searchTerm);
	void changeViewType(int newViewType);
	void changeSaveDirectory(string newSaveDirectory);
	void saveToTxtFile();
	void saveLastChange();

	void executeCommand(string command);
	void executeSearchCommand(string command);
	void vectorToTaskList(vector<string>& existingData);
	vector<string> taskListToVector();
	bool outOfRange(int index);
	bool dateSort(Task* a, Task* b);
	bool timeSort(Task* a, Task* b);
	bool foundInTask(Task* task, string searchTerm);
	bool isNotValidDirectory(string newSaveDirectory);
	int stringToInteger(string text);
	string integerToString(int integer);
	int getCurrentDate();
	int getSearchIndex(CommandPackage* commandPackage);
};