#pragma once

#ifndef STORAGE_H
#define STORAGE_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Storage class simply:
//	1) holds the directory or file address of chosen .txt file as a private member attribute, that can be changed via
//	   changeLocation() member function. 
//	2) extracts content from user-specified .txt file database into a string vector for the usage of other classes, by
//	   returning the string vector from retrieveData()
//	3) overwrites the .txt file database content with that of the string vector passed into the parameter of saveData()

class Storage {
private:
	//string _location;
	// to check whether file is already created, or physically available, in given directory
	bool _isFileCreated;

public:
	Storage();

	vector<string> getExistingData(string saveDirectory);
	void saveUpdatedData(vector<string>, string saveDirectory);
	void changeLocation(string);
};

#endif

