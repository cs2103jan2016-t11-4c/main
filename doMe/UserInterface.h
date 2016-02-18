#pragma once
#include <iostream>
#include <string>

using namespace std;

class UserInterface {
private:
	string _textFileName;

	char buffer[255];

public:
	UserInterface(void);
	~UserInterface(void);
	//void display();
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

	void updateTextFileName(string newTextFileName);

	void printFirstTimeUserPrompt();
	void printFirstTimeUserDirectoryPrompt();
	void printChangeSaveFileDirectory(string newDirectory);
	void printInvalidSaveFileDirectory();
	void printChangeSaveFileDirectory();
	void showToUser(string string);
};

