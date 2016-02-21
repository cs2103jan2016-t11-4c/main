#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "Task.h"
using namespace std;

class UserInterface {
private:
	
	char buffer[255];

	void showToUser(string string); //core helper
public:
	UserInterface(void);
	~UserInterface(void);

	void printWelcomeNotification();
	//void printDataWithNumbering();
	void printAddNotification(string name, int date1, int date2, int time1, int time2, string location);
	void printInvalidAddNotification();
	void printEmptyNotification();
	void printDeleteNotification(int index);
	void printInvalidDeletionNotification();
	void printClearNotification();
	void printSearchNotification(string text, int index);
	void printInvalidCommandNotification();
	void printPromptCommand();	//prints Ågcommand:Åh

	void printTaskList(vector<Task*> *taskList, int currentDate ,int viewType);  //complete view all task not refactored
	
	void printPromptFirstTimeUser(); //complete
	void printPromptFirstTimeUserDirectory(); //complete

	void printNotificationChangeSaveFileDirectory(string newDirectory); //complete
	void printNotificationInvalidSaveFileDirectory(); //complete
	void printNotificationEmptySaveFileDirectory();  //complete

	string getTaskString(Task* individualTask, int viewType) ; //doing helper
};

