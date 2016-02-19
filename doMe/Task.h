#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <windows.h>
#include <vector>

using namespace std;

class Task {
public:
	Task(void);
	~Task(void);
	string getFirstDate();
	string getTaskString();
};

