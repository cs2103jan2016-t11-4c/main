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

	static const string FILE_SETTINGS_NAME;
    static const string DEFAULT_TEXT_FILE_NAME;
	static const string VOID_INDICATOR;
	static const string VOID_STRING;

	string _textFileName;
	string _saveDirectory;
	int _viewType; //temporary this first before we finalise naming
 
	string createValidTextFileNameString(string textFileName); //helper input test return test.txt
    string createValidFileDirectoryString(string directory); //helper input return directory with "/"
	bool checkValidityOfDirectory(const string& directory); //might remove
	void openNewSettingFile(); //complete
	string writeSettingsDetails(string sentence); //helper for writing process
	string loadSettingsDetails(string sentence); //helper for loading process
	string promptForTextName(); // complete
	
public:
	Settings(void);
	~Settings(void);

    //complete
    void changeSaveDirectory(string directory); //only insert directory without text file name
	void updateTextFileName(string textFileName);
    bool checkEmptySaveDirectory(); 
	bool checkForSettingsFile();
	string getSaveDirectory();
    string getTextFileName();
    int getViewType();
    void changeViewType(int newViewType);
	void loadSettings(); 
	void saveSettings(); 	

};

