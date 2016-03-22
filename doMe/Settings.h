#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <windows.h>

using namespace std;


class Settings {
public:
    Settings(void);
    ~Settings(void);

    //setter
	void changeSaveDirectory(string directory); //API for Memory component
	void updateTextFileName(string textFileName);
    bool changeViewType(int newViewType); //API for Memory compoent
    //getter
	string getSaveDirectory();
    string getTextFileName();
    int getViewType();
    
    void resizeWindow(); //API for Memory component
    bool loadSettings(); //placed in constructor of Settings; boolean return value to be reconsidered
    void saveSettings(); //placed in every setter function, in order save changes to settings.txt	

	bool checkEmptySaveDirectory(); 
    bool checkForSettingsFile();
    
#ifndef TESTMODE 
private: 
#else 
public: 
#endif

    static const string FILE_SETTINGS_NAME;
    static const string DEFAULT_TEXT_FILE_NAME;
    static const string VOID_INDICATOR;
    static const string VOID_STRING;
    static const string SYSTEM_MODE_CON;
    static const int DEFAULT_WINDOWS_WIDTH;
    static const int DEFAULT_WINDOWS_LENGTH; 

    string _textFileName;
    string _saveDirectory;
    int _viewType; //temporary this first before we finalise naming
    char buffer[255];

    string createValidTextFileNameString(string textFileName); //helper input test return test.txt
    string createValidFileDirectoryString(string directory); //helper input return directory with "/"
    bool checkValidityOfDirectory(const string& directory); //might remove
    void openNewSettingFile(); //complete
    string writeSettingsDetails(string sentence); //helper for writing process
    string loadSettingsDetails(string sentence); //helper for loading process
    string promptForTextName(); // complete

};

