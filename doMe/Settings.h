#pragma once
#include "Core.h"

class Settings {
#ifndef TESTMODE 
private: 
#else 
public: 
#endif

	static const string FILE_NAME_SETTINGS;
	static const string VOID_INDICATOR;
	static const string VOID_STRING;

	string _textFileName;
	string _saveDirectory;
	int _viewType; //temporary this first before we finalise naming

	bool checkForSettingsFile(); //complete
	void firstTimeUser(); // complete
	string createTextFileNameString(string textFileName); //helper 
	bool checkValidityOfDirectory(const string& directory); //helper
	void openNewSettingFile(); // complete
	string writeSettingsDetails(string sentence); //helper
	string loadSettingsDetails(string sentence); //helper 

	void loadSettings(); // complete
	void saveSettings(); // complete

	std::string promptForTextName(); // complete
	void writeTextFiletoDataFile(); //call storage
	void openNewTextFile(); //call storage
	void checkEmptySaveDirectory(); // complete

public:
	Settings(void);
	~Settings(void);
	void setEnvironment(); //doing
	void updateTextFileName(string textFileName);
	void changeDirectory(string directory);
	string getDirectory(); //getter function to pass to storage
};

