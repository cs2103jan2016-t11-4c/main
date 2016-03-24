#include "Storage.h"

Storage* Storage::_instance = 0;

Storage* Storage::getInstance() {
	if (_instance == 0) {
		_instance = new Storage;
	}
	return _instance;	
}

Storage::Storage() {

}

vector<string> Storage::retrieveData(string directory) {
    vector<string> dataVector;
	string tempText;
    ifstream readFile;

    readFile.open(directory);

    if (readFile.is_open()) {
        while (getline(readFile, tempText)) {
            dataVector.push_back(tempText);
        }
        readFile.close();
    }
    else {
//    	throw string("An error has occurred when reading " + directory);
    }
	
	return dataVector;
}

void Storage::saveData(vector<string> updatedData, string directory) {
    ofstream writeFile;
    writeFile.open(directory);

    if (writeFile.is_open()) {
        for (int i = 0; i != updatedData.size(); i++) {
            writeFile << updatedData[i] << endl;
        }
        writeFile.close();
    }
    else {
//    	throw string("An error has occurred when saving to " + directory);
    }
}

