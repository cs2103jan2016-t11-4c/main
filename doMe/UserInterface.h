#pragma once
#include "Core.h"

class UserInterface {
private:
	string _textFileName;
	char buffer[255];

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

	void printTaskList(vector<Task*> *taskList, string currentDate ,int viewType); //complete view all task not refactored
	void updateTextFileName(string newTextFileName); //complete
	void printFirstTimeUserPrompt(); //complete
	void printFirstTimeUserDirectoryPrompt(); //complete
	void printChangeSaveFileDirectory(string newDirectory); //complete
	void printInvalidSaveFileDirectory(); //complete
	void printChangeSaveFileDirectory(); //complete
	void showToUser(string string); //core helper
};

