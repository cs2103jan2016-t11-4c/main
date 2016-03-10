#include "Storage.h"

Storage::Storage()
{
    _isFileCreated = false;
}

/*void Storage::setLocation(string directory) {
    _location = directory + "todo.txt";
}*/

vector<string> Storage::retrieveData(string directory) {
    vector<string> dataVector;
    string tempText;
    ifstream readFile;

    /*setLocation(directory);*/

    readFile.open(directory);

    if (readFile.is_open()) {
        while (getline(readFile, tempText)) {
            dataVector.push_back(tempText);
        }
    }
    else {
        _isFileCreated = true;
        cerr << "File " << directory << " does not exist yet" << endl; //let UI print
    }

    readFile.close();

    return dataVector;
}

void Storage::saveData(vector<string> updatedData, string directory) {
    ofstream writeFile;

    /*setLocation(directory);*/

    writeFile.open(directory);

    if (writeFile.is_open()) {
        if (_isFileCreated) {
            cout << directory << " has just been newly created! Your changes will be saved here." << endl; //let UI print
        }

        for (int i = 0; i != updatedData.size(); i++) {
            writeFile << updatedData[i] << endl;
        }
    }
    else {
        cerr << "There is an error in opening file " << directory << endl; //let UI print
    }

    writeFile.close();
}

