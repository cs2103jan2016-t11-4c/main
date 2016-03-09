#include "Storage.h"

Storage::Storage()
{
	_isFileCreated = false;
}

void Storage::setLocation(string directory)
{
	_location = directory + _txtFileName;
}

vector<string> Storage::retrieveData(string directory)
{
	vector<string> dataVector;
	string tempText;
	ifstream readFile;

	setLocation(directory);

	readFile.open(_location);

	if (readFile.is_open()) {
		while (getline(readFile, tempText)) {
			dataVector.push_back(tempText);
		}
	}
	else {
		_isFileCreated = true;
		cerr << "File " << _location << " does not exist yet" << endl;
	}

	readFile.close();

	return dataVector;
}

void Storage::saveData(vector<string> updatedData, string directory)
{
	ofstream writeFile;

	setLocation(directory);

	writeFile.open(_location);

	if (writeFile.is_open()) {
		if (_isFileCreated) {
			cout << _location << " has just been newly created! Your changes will be saved here." << endl;
		}

		for (int i = 0; i != updatedData.size(); i++) {
			writeFile << updatedData[i] << endl;
		}
	}
	else {
		cerr << "There is an error in opening file " << _location << endl;
	}

	writeFile.close();
}

