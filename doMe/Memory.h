#pragma once
#include <list>
#include <string>
#include "RAM.h"
#include "Settings.h"

class Memory {
private:
	RAM* _ram;
	Settings* _settings;
	
	static Memory* _instance;
	Memory();

public:
	static Memory* getInstance();

	//accessing Settings class object
	void changeSaveDirectory(string);
	bool changeViewType(int);
	void resizeWindow();

	//accessing RAM class object
	//... pending API decisions
};
