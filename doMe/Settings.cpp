#include "Settings.h"
const string Settings::FILE_SETTINGS_NAME = "settings.txt";
const string Settings::DEFAULT_TEXT_FILE_NAME = "doMe.txt";
const string Settings::SYSTEM_MODE_CON = "mode CON: COLS=%d lines=%d";
const int Settings::DEFAULT_WINDOWS_WIDTH = 80;
const int Settings::DEFAULT_WINDOWS_LENGTH = 25; 

Settings* Settings::_instance = 0;

Settings* Settings::getInstance() {
    if (_instance == 0) {
        _instance = new Settings;
    }
    return _instance;
}

Settings::Settings(void) {
    _textFileName = DEFAULT_TEXT_FILE_NAME;
    _viewType = 0;
    loadSettings(); //easier for constructor of Memory class -joan
}

Settings::~Settings(void) {
}

/****************************************************************/

void Settings::loadSettings() {
    Storage* storage;
    storage = Storage::getInstance();
    try {
    settingsLoadVector(storage->retrieveData(FILE_SETTINGS_NAME));
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
    int columns;
    int rows;
    _textFileName = existingData[i];
    _saveDirectory = existingData[i+1];
    _viewType = stringToInteger(existingData[i+2]);
    columns = stringToInteger(existingData[i+3]);
    rows = stringToInteger(existingData[i+4]);

    //change window size
    sprintf_s(buffer, SYSTEM_MODE_CON.c_str(), columns , rows);
    system(buffer);

}

vector<string> Settings::settingsGetVector() {
    vector<string> updatedData;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;
    int rows;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    updatedData.push_back(_textFileName);
    updatedData.push_back(_saveDirectory);
    updatedData.push_back(integerToString(_viewType));
    updatedData.push_back(integerToString(columns));
    updatedData.push_back(integerToString(rows));
    return updatedData;
}

/****************************************************************/

void Settings::changeSaveDirectory(string directory) {
    string newDirectory;
    newDirectory = createValidFileDirectoryString(directory);
    _saveDirectory = newDirectory;
    saveSettings(); //adding saveSettings() to all setter functions in Settings class; some redundancy may need further refactoring -joan
}

bool Settings::changeViewType(int newViewType) {
    _viewType = newViewType;
    saveSettings(); //adding saveSettings() to all setter functions in Settings class; some redundancy may need further refactoring -joan
    return true;
}

void Settings::changeTextFileName(string textFileName) {
    string newTextFileName;

    newTextFileName = createValidTextFileNameString(textFileName);

    _textFileName = newTextFileName;

    saveSettings(); //adding saveSettings() to all setter functions in Settings class, some redundancy may need further refactoring -joan
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

void Settings::resizeWindow() {
    sprintf_s(buffer, SYSTEM_MODE_CON.c_str(), DEFAULT_WINDOWS_WIDTH , DEFAULT_WINDOWS_LENGTH);
    system(buffer);
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
//helper function to make correct format of textfile name
string Settings::createValidTextFileNameString(string textFileName) {
    string fileExtension = ".txt";
    if(textFileName.substr(textFileName.find_last_of(".") + 1) == "txt") {
        return textFileName;
    } else {
        return(textFileName + fileExtension);
    }
}

//helper function to make correct format of save directory
string Settings::createValidFileDirectoryString(string directory) {
    string fileSeparator= "/";
    if(directory.find_last_of("/\\")+1 == directory.size()) {
        return directory;
    } else {
        return directory + fileSeparator;
    }
}

/****************************************************************/

//all may be redundant / remove if necessary
void Settings::openNewSettingFile() {
    std::ofstream writeFile;

    writeFile.open(FILE_SETTINGS_NAME);
}

bool Settings::checkForSettingsFile() {
    ifstream settingFile(FILE_SETTINGS_NAME);

    if (settingFile.is_open()) {
        return true;
    } else {
        return false;
    }
}

bool Settings::checkEmptySaveDirectory() {
    if(_saveDirectory.empty()) {
        return false;
    } else {
        return true;
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
