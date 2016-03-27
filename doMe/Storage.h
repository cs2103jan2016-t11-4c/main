#pragma once

#ifndef STORAGE_H
#define STORAGE_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Exception_FileCannotOpen.h"

using namespace std;

// Storage class simply:
//	1) extracts content from .txt file into a string vector for usage by other classes, and
//	2) overwrites the .txt file content with that of the string vector passed into the parameter of saveData()

class Storage {
private:
	static Storage* _instance;
	Storage();
	
public:
	static Storage* getInstance();

	// extract data from directory and returns data as a string vector
	// throw exception when ifstream .txt file cannot be opened
	vector<string> retrieveData(string);

	// save the string vector pass as parameter into directory
	// throw exception when ofstream .txt file cannot be opened
	void saveData(vector<string>, string);

    void openDefaultNewFile(string fileName); 
};

#endif


