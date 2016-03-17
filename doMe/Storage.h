#pragma once

#ifndef STORAGE_H
#define STORAGE_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Storage class simply:
//	1) extracts content from todo.txt into a string vector for the usage by other classes, by
//	   returning this string vector as pass-by-reference parameter from retrieveData()
//	2) overwrites the todo.txt file content with that of the string vector passed into the parameter of saveData()

class Storage {
private:
	// for potential function of checking whether file is already created, or physically available, in given directory
	bool _isFileCreated;

public:
	// initialise _isFileCreated as false
	Storage();

	// extract data from directory and pass resulting vector string by reference
	// returns boolean variable to indicate whether ifstream .txt file can be opened
	bool retrieveData(vector<string>&, string);

	// save current string vector into directory
	// returns boolean variable to indicate whether ofstream .txt file can be opened
	bool saveData(vector<string>, string);

};

#endif


