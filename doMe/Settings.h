#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <windows.h>
#include "Storage.h"
using namespace std;


class Settings {
private:
    static Settings* _instance;
    Settings(void);
    ~Settings(void);
public:
    /*Settings(void);
    ~Settings(void);*/
    static Settings* getInstance();

    //setter
    void changeSaveDirectory(string directory); //API for Memory component
    void changeTextFileName(string textFileName);
    bool changeViewType(int newViewType); //API for Memory compoent
    //getter
    string getSaveDirectory();
    string getTextFileName();
    int getViewType();

    void resizeWindow(); //API for Memory component
    void loadSettings(); //placed in constructor of Settings; boolean return value to be reconsidered
    void saveSettings(); //placed in every setter function, in order save changes to settings.txt	

    void settingsLoadVector(vector<string> &existingData);
    vector<string> settingsGetVector();
    string integerToString(int integer);
    int stringToInteger(string& text);

    bool checkEmptySaveDirectory(); 
    bool checkForSettingsFile();

#ifndef TESTMODE 
private: 
#else 
public: 
#endif

    static const string FILE_SETTINGS_NAME;
    static const string DEFAULT_TEXT_FILE_NAME;
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
    string promptForTextName(); // complete

};

