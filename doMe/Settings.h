#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <windows.h>
#include "UserInterface.h"
using namespace std;

class Settings {
#ifndef TESTMODE 
private: 
#else 
public: 
#endif

	static const string FILE_SETTINGS;

	string _textFileName;
	string _saveDirectory;
	int _viewType; //temporary this first before we finalise naming

	bool checkForSettingsFile(); //complete
	void firstTimeUser();
	string createTextFileNameString(string textFileName); //helper 
	bool checkValidityOfDirectory(const string& directory); //helper

	void loadSettings();
	void saveSettings();

	std::string promptForTextName();
	void writeTextFiletoDataFile(); //call storage
	void openNewTextFile(); //call storage
	void checkEmptySaveDirectory();

public:
	Settings(void);
	~Settings(void);
	void setEnvironment();
	void updateTextFileName(string textFileName);
	void changeDirectory(string directory);
	string getDirectory(); //getter function
};

