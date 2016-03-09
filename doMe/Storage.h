#pragma once

#ifndef STORAGE_H
#define STORAGE_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Storage class simply:
//	1) extracts content from todo.txt*** file in user-specified directory into a string vector for the usage of other classes, by
//	   returning the string vector from retrieveData()
//	2) overwrites the todo.txt file content with that of the string vector passed into the parameter of saveData()
//	
//	***If todo.txt does not exist yet, indicates user is using for the first time, and todo.txt will be created after first entry
//	or operation in given directory.

class Storage {
private:
	string _location;
	/*string _txtFileName = "todo.txt";*/
	// to check whether file is already created, or physically available, in given directory
	bool _isFileCreated;

public:
	// initialise _isFileCreated as false
	Storage();
	
	// concatenate directory with default _txtFileName to get exact target .txt
	// file destination (_location) such that fstream can open it effectively
	// also, a setter function for file destination changes
	void setLocation(string);

	// extract data from target .txt file and return as string vector
	vector<string> retrieveData(string);

	// save current string vector into target .txt file
	void saveData(vector<string>, string);

};

#endif


