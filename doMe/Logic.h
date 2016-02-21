#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sys/types.h>
#include <sys/stat.h>
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
	UserInterface* _UI;
	Storage* _storage;
	Settings* _settings;
public:
	Logic();
	void setEnvironment();
	void displayWelcomeMessage();
	void executeCommandsUntilExitCommand();

	void add(Task* task);
	void display();
	void del(int index);
	void edit(int index, Task* task);
	void clear();
	void undo();
	void sort();
	void search(string searchTerm);
	void changeViewType(int newViewType);
	void changeSaveDirectory(string newSaveDirectory);
	void saveToTxtFile();
	void saveLastChange();

	void executeCommand(string command);
	void vectorToTaskList(vector<string>& existingData);
	vector<string> taskListToVector();
	int outOfRange(int index);
	bool dateSort(Task* a, Task* b);
	bool timeSort(Task* a, Task* b);
	int wordFoundInEntry(string text, string entry);
	int isNotValidDirectory(string newSaveDirectory);
	int stringToInteger(string text);
	string integerToString(int integer);
	int getDateToday();
};
