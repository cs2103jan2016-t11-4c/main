#pragma once
#include <list>
#include <string>
#include "RAM.h"
#include "Settings.h"

class MemoryV2 {
private:
	RAM* _ram;
	Settings* _settings;
	
	static MemoryV2* _instance;
	MemoryV2();

public:
	static MemoryV2* getInstance();

	//accessing Settings class object
	void changeSaveDirectory(string);
	bool changeViewType(int);
	void resizeWindow();

	//accessing RAM class object
	//... pending API decisions
};