#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sys/types.h>
#include <sys/stat.h>
#include "UI.h"
#include "Task.h"
#include "Parser.h"
#include "Storage.h"
#include "Settings.h"
using namespace std;

class Logic { 
private:
	vector<Task*> _taskList;
	vector<Task*> _prevTaskList;
	UI* _UI;
	Storage* _storage;
	Settings* _settings;
public:
	Logic();
	void setEnvironment();
	void displayWelcomeMessage();
	void executeCommandsUntilExitCommand();

	void add(string name, int date1, int date2, int time1, int time2, string location);
	void display();
	void del(int index);
	void edit(int index, string name, int date1, int date2, int time1, int time2, string location);
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
};