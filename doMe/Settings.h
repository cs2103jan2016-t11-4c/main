//@@author A0130475L
#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <windows.h>
#include "Storage.h"
#include "Exception_FirstTimeUser.h"
using namespace std;


class Settings {
public:
    static Settings* getInstance();

    //setter
    bool changeSaveDirectory(string directory); //API for Memory component
    bool changeViewType(int newViewType); //API for Memory compoent
    void changeWindowSize(int column, int row);
    //getter
    string getSaveDirectory();
    string getTextFileName();
    int getViewType();
    void getWindowSize(int& width, int& length);

    void loadSettings(); //placed in constructor of Settings; boolean return value to be reconsidered

#ifndef TESTMODE 
private: 
#else 
public: 
#endif

    static const string FILE_SETTINGS_NAME;
    static const string DEFAULT_TEXT_FILE_NAME;
    static const string SYSTEM_MODE_CON;
    static const int DEFAULT_VIEWTYPE;
    static const int DEFAULT_WINDOWS_WIDTH;
    static const int DEFAULT_WINDOWS_LENGTH; 

    static Settings* _instance;
    string _textFileName;
    string _saveDirectory;
    int _viewType; 
    int _width;
    int _length;
    char buffer[255];

    Settings(void);
    ~Settings(void);

    void settingsLoadVector(vector<string> &existingData);
    vector<string> settingsGetVector();

    string createValidFileDirectoryString(string directory); //helper input return directory with "/"
    bool checkValidityOfDirectory(const string& directory); //might remove

    string integerToString(int integer);
    int stringToInteger(string& text);

    void saveSettings(); //placed in every setter function, in order save changes to settings.txt	

};

