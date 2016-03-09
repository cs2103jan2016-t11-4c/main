#include "Storage.h"

Storage::Storage()
{
	//_location = location;
	_isFileCreated = false;
}

vector<string> Storage::getExistingData(string saveDirectory)
{
	vector<string> dataVector;
	string tempText;
	ifstream readFile;

	readFile.open(saveDirectory);

	if (readFile.is_open()) {
		while (getline(readFile, tempText)) {
			dataVector.push_back(tempText);
		}
	}
	else {
		_isFileCreated = true;
		cerr << "File " << saveDirectory << " does not exist yet" << endl;
	}

	readFile.close();

	return dataVector;
}

void Storage::saveUpdatedData(vector<string> updatedData, string saveDirectory)
{
	ofstream writeFile;

	writeFile.open(saveDirectory);

	if (writeFile.is_open()) {
		if (_isFileCreated) {
			cout << saveDirectory << " has just been newly created! Your changes will be saved here." << endl;
		}

		for (int i = 0; i != updatedData.size(); i++) {
			writeFile << updatedData[i] << endl;
		}
	}
	else {
		cerr << "There is an error in opening file " << saveDirectory << endl;
	}

	writeFile.close();
}
/*
void Storage::changeLocation(string newLocation)
{
	_location = newLocation;
}
*/
