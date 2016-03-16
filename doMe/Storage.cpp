#include "Storage.h"

Storage::Storage()
{
    _isFileCreated = false;
}

/*void Storage::setLocation(string directory) {
    _location = directory + "todo.txt";
}*/

bool Storage::retrieveData(vector<string>& data, string directory) {
    string tempText;
    ifstream readFile;

    readFile.open(directory);

    if (readFile.is_open()) {
        while (getline(readFile, tempText)) {
            data.push_back(tempText);
        }
        readFile.close();
        return true;
    }
    else {
        _isFileCreated = true;
        /*cerr << "File " << directory << " does not exist yet" << endl;*/ //let UI print
        return false;
    }

}

bool Storage::saveData(vector<string> updatedData, string directory) {
    ofstream writeFile;
    bool canFileOpen;

    writeFile.open(directory);

    if (writeFile.is_open()) {
        /*if (_isFileCreated) {
            cout << directory << " has just been newly created! Your changes will be saved here." << endl; //let UI print
        }*/
        for (int i = 0; i != updatedData.size(); i++) {
            writeFile << updatedData[i] << endl;
        }
        writeFile.close();
        return true;
    }
    else {
        /*cerr << "There is an error in opening file " << directory << endl; //let UI print*/
        return false;
    }

}

