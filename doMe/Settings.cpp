//@@author A0130475L
#include "Settings.h"
const string Settings::FILE_SETTINGS_NAME = "doMeSettings.txt";
const string Settings::DEFAULT_TEXT_FILE_NAME = "doMe.txt";
const int Settings::DEFAULT_VIEWTYPE = 1;
const int Settings::DEFAULT_WINDOWS_WIDTH = 80;
const int Settings::DEFAULT_WINDOWS_LENGTH = 35; 

Settings* Settings::_instance = 0;

Settings* Settings::getInstance() {
    if (_instance == 0) {
        _instance = new Settings;
    }
    return _instance;
}

Settings::Settings(void) {
    _textFileName = DEFAULT_TEXT_FILE_NAME;
    _viewType = DEFAULT_VIEWTYPE;
    _width = DEFAULT_WINDOWS_WIDTH;
    _length = DEFAULT_WINDOWS_LENGTH;
}

Settings::~Settings(void) {
}

/****************************************************************/

void Settings::loadSettings() {
    Storage* storage;
    storage = Storage::getInstance();
    try {
        ifstream readFile(FILE_SETTINGS_NAME);
        if(readFile.is_open()) {
            settingsLoadVector(storage->retrieveData(FILE_SETTINGS_NAME));
        } else {
            saveSettings();
            throw Exception_FirstTimeUser();
        }
    } catch (Exception_FileCannotOpen e) {
        saveSettings();
    }
}

void Settings::saveSettings() {
    Storage* storage;
    storage = Storage::getInstance();
    storage->saveData(settingsGetVector() ,FILE_SETTINGS_NAME);
}

/****************************************************************/

void Settings::settingsLoadVector(vector<string> &existingData) {
    int i = 0;

    _textFileName = existingData[i];
    _saveDirectory = existingData[i+1];
    _viewType = stringToInteger(existingData[i+2]);
    _width = stringToInteger(existingData[i+3]);
    _length = stringToInteger(existingData[i+4]);

}

vector<string> Settings::settingsGetVector() {
    vector<string> updatedData;

    updatedData.push_back(_textFileName);
    updatedData.push_back(_saveDirectory);
    updatedData.push_back(integerToString(_viewType));
    updatedData.push_back(integerToString(_width));
    updatedData.push_back(integerToString(_length));
    return updatedData;
}

/****************************************************************/

bool Settings::changeSaveDirectory(string directory) {
    string newDirectory;
    newDirectory = createValidFileDirectoryString(directory);
    if(directory.empty()) {
        _saveDirectory = directory;
        return true;
    }
    if(checkValidityOfDirectory(newDirectory)) {
        _saveDirectory = newDirectory;
        saveSettings(); //adding saveSettings() to all setter functions in Settings class; some redundancy may need further refactoring -joan
        return true;   
    } else {
        return false;
    }
}

bool Settings::changeViewType(int newViewType) {
    if((newViewType >= 0) && (newViewType <= 3)) {
        _viewType = newViewType;
        saveSettings(); //adding saveSettings() to all setter functions in Settings class; some redundancy may need further refactoring -joan
        return true;
    } else {
        return false;
    }
}

void Settings::changeWindowSize(int column, int row) {
    _width = column;
    _length = row;
    saveSettings();
}

/****************************************************************/

string Settings::getSaveDirectory() {
    return (_saveDirectory /*+ _textFileName*/);   //getSaveDirectory() should return the main directory w/o specific txt filename so that 
    //it can be generalised for settings.txt & doMe.txt & logs.txt etc etc
    //pre-condition: all these .txt files must be in same directory
}

int Settings::getViewType() {
    return _viewType;
}

string Settings::getTextFileName() {
    return _textFileName;
}

void Settings::getWindowSize(int& width, int& length) {
    width = _width;
    length = _length;
}

/****************************************************************/

string Settings::integerToString(int integer) {
    ostringstream word;
    word << integer;
    return word.str();
}

int Settings::stringToInteger(string& text) {
    stringstream ss(text);
    int integer;

    ss >> integer;

    return integer;
}

/****************************************************************/

//helper function to make correct format of save directory
string Settings::createValidFileDirectoryString(string directory) {
    string fileSeparator= "\\";
    if(directory.find_last_of("\\")+1 == directory.size()) {
        return directory;
    } else {
        return directory + fileSeparator;
    }
}

//https://msdn.microsoft.com/en-us/library/windows/desktop/bb773584(v=vs.85).aspx
bool Settings::checkValidityOfDirectory(const string& directory) {
    DWORD ftyp = GetFileAttributesA(directory.c_str());
    if (ftyp == INVALID_FILE_ATTRIBUTES) {
        return false;  
    }
    if (ftyp & FILE_ATTRIBUTE_DIRECTORY) {
        return true;   
    }

    return false;    
}
