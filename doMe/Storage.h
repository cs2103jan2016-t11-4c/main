#pragma once
#include <vector>
#include <string>
#include "Task.h"

using namespace std;

class Storage {
public:
	Storage(void);
	~Storage(void);

	void saveUpdatedData(vector<string> updatedData, string saveDirectory);
	vector<string> getExistingData(); 			 	
};


