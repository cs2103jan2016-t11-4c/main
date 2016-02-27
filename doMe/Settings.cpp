#include "Settings.h"
const string Settings::FILE_NAME_SETTINGS = "settings.txt";
const string Settings::VOID_INDICATOR = "-";
const string Settings::VOID_STRING = "";


Settings::Settings(void) {
}

Settings::~Settings(void) {
}

void Settings::loadSettings() {
	ifstream readFile(FILE_NAME_SETTINGS);
	string extractedSettings;
    

	getline(readFile, extractedSettings);
	_textFileName = loadSettingsDetails(extractedSettings);

	getline(readFile, extractedSettings);
	_saveDirectory = loadSettingsDetails(extractedSettings);

    getline(readFile, extractedSettings);
    istringstream iss(loadSettingsDetails(extractedSettings));
    iss >> _viewType;
}

void Settings::saveSettings() {
	ofstream writeFile;
    stringstream convert;
    string viewType;
	writeFile.close(); //close and reopen file to refresh the data file for overwriting
	writeFile.open(FILE_NAME_SETTINGS);

    convert << _viewType;
    viewType = convert.str();
	writeFile << writeSettingsDetails(_textFileName) << endl;
	writeFile << writeSettingsDetails(_saveDirectory) << endl;
    writeFile << writeSettingsDetails(viewType) << endl;
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

	writeFile.open(FILE_NAME_SETTINGS);
}

bool Settings::checkForSettingsFile() {
	std::ifstream settingFile(FILE_NAME_SETTINGS);

	if (settingFile.is_open()) {
		return true;
	} else {
		return false;
	}
}

void Settings::updateTextFileName(string sentence) {
	istringstream iss(sentence);
	string textFileName;

	iss >> textFileName;

	_textFileName = createTextFileNameString(textFileName);
}

string Settings::createTextFileNameString(string textFileName) {
	string fileExtension = ".txt";
	if(textFileName.substr(textFileName.find_last_of(".") + 1) == "txt") {
		return textFileName;
	} else {
		return(textFileName + fileExtension);
		//textFileName.insert(textFileName.end(),".txt"); doesn't work? why?
	}
}

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

	if(checkValidityOfDirectory(extractedDirectory) == true) {
		UserInterface UI;
		_textFileName = textFileName;
		_saveDirectory = extractedDirectory;

		UI.printNotificationChangeSaveFileDirectory(getSaveDirectory());
	} else {
		UserInterface UI;
		UI.printNotificationInvalidSaveFileDirectory();
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