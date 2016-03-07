#include "Settings.h"
const string Settings::FILE_SETTINGS_NAME = "settings.txt";
const string Settings::VOID_INDICATOR = "-";
const string Settings::VOID_STRING = "";
const string Settings::DEFAULT_TEXT_FILE_NAME = "doMe.txt";
const string Settings::SYSTEM_MODE_CON = "mode CON: COLS=%d lines=%d";
const int Settings::DEFAULT_WINDOWS_WIDTH = 80;
const int Settings::DEFAULT_WINDOWS_LENGTH = 25; 

Settings::Settings(void) {
    _textFileName = DEFAULT_TEXT_FILE_NAME;
    _viewType = -1;
}

Settings::~Settings(void) {
}

void Settings::loadSettings() {
    ifstream readFile(FILE_SETTINGS_NAME);
    stringstream is;
    string extractedSettings;
    int columns;
    int rows;

    if(checkForSettingsFile()) {
        getline(readFile, extractedSettings);
        _textFileName = loadSettingsDetails(extractedSettings);

        getline(readFile, extractedSettings);
        _saveDirectory = loadSettingsDetails(extractedSettings);

        getline(readFile, extractedSettings);
        is << (loadSettingsDetails(extractedSettings));
        is >> _viewType;

        is.clear();
        getline(readFile, extractedSettings);
        is << (loadSettingsDetails(extractedSettings));
        is >> columns;

        is.clear();
        getline(readFile, extractedSettings);
        is << (loadSettingsDetails(extractedSettings));
        is >> rows;

        sprintf_s(buffer, SYSTEM_MODE_CON.c_str(), columns , rows);
        system(buffer);

    } else {
        saveSettings();
    }
}

void Settings::saveSettings() {
    ofstream writeFile;
    stringstream convert;
    string viewType;
    string c;
    string r;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;
    int rows;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    writeFile.close(); //close and reopen file to refresh the data file for overwriting
    writeFile.open(FILE_SETTINGS_NAME);

    writeFile << writeSettingsDetails(_textFileName) << endl;

    writeFile << writeSettingsDetails(_saveDirectory) << endl;

    convert << _viewType;
    viewType = convert.str();
    writeFile << writeSettingsDetails(viewType) << endl;

    convert << columns;
    c = convert.str();
    writeFile << writeSettingsDetails(c) << endl;

    convert << rows;
    r = convert.str();
    writeFile << writeSettingsDetails(r) << endl;
}

string Settings::writeSettingsDetails(string sentence) {
    if(sentence.empty()) {
        return VOID_INDICATOR;
    } else {
        return sentence;
    }
}

string Settings::loadSettingsDetails(string sentence) {
    if(sentence == VOID_INDICATOR) {
        return VOID_STRING;
    } else {
        return sentence;
    }
}

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

void Settings::updateTextFileName(string textFileName) {
    string newTextFileName;

    newTextFileName = createValidTextFileNameString(textFileName);

    _textFileName = newTextFileName;
}

string Settings::createValidTextFileNameString(string textFileName) {
    string fileExtension = ".txt";
    if(textFileName.substr(textFileName.find_last_of(".") + 1) == "txt") {
        return textFileName;
    } else {
        return(textFileName + fileExtension);
    }
}

string Settings::createValidFileDirectoryString(string directory) {
    string fileSeparator= "/";
    if(directory.find_last_of("/\\")+1 == directory.size()) {
        return directory;
    } else {
        return directory + fileSeparator;
    }
}
/*
void Settings::changeSaveDirectory(string directory) { //need refactoring
//delete old text file?
size_t found;
string extractedDirectory;
string textFileName;

//check for existing txt file inputted 
//extract correct data
if(directory.substr(directory.find_last_of(".") + 1) == "txt") {
found = directory.find_last_of("/\\");
extractedDirectory = directory.substr(0,found+1);
textFileName = directory.substr(found+1);
} else {
if(directory.find_last_of("/\\")+1 == directory.size()) {
extractedDirectory = directory;
textFileName = _textFileName;
} else {
extractedDirectory = directory;
textFileName = _textFileName;
extractedDirectory = (extractedDirectory + "/");
}
}

_textFileName = textFileName;
_saveDirectory = extractedDirectory;

if(checkValidityOfDirectory(extractedDirectory) == true) {
UserInterface UI;


UI.printNotificationChangeSaveFileDirectory(getSaveDirectory());
} else {
UserInterface UI;
UI.printNotificationInvalidSaveFileDirectory();
}

}
*/
void Settings::changeSaveDirectory(string directory) {
    string newDirectory;
    newDirectory = createValidFileDirectoryString(directory);
    _saveDirectory = newDirectory;

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

string Settings::getSaveDirectory() {
    return(_saveDirectory+_textFileName);
}

bool Settings::checkEmptySaveDirectory() {
    if(_saveDirectory.empty()) {
        return false;
    } else {
        return true;
    }
}

int Settings::getViewType() {
    return _viewType;
}

void Settings::changeViewType(int newViewType) {
    _viewType = newViewType;
}

string Settings::getTextFileName() {
    return _textFileName;
}

void Settings::resizeWindow() {
        sprintf_s(buffer, SYSTEM_MODE_CON.c_str(), DEFAULT_WINDOWS_WIDTH , DEFAULT_WINDOWS_LENGTH);
        system(buffer);
}