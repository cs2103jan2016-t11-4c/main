#pragma once
#include <vector>
#include <string>
#include "Task.h"

using namespace std;

class Storage {
public:
	Storage(void);
	~Storage(void);
	void saveUpdatedData(vector<Task*> *taskList, string saveDirectory);
	vector<Task*>* getExistingData(); 			 	
	void changeSaveDirectory(string url);
};



