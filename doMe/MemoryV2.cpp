#include "MemoryV2.h"

MemoryV2* MemoryV2::_instance = 0;

MemoryV2* MemoryV2::getInstance()
{
	if (_instance == 0) {
		_instance = new MemoryV2;
	}
	return _instance;
}

MemoryV2::MemoryV2() 
{
	_settings = Settings::getInstance(); //main functionality from Settings constructor
	_ram = RAM::getInstance();			 //main functionality from RAM constructor
}

void MemoryV2::changeSaveDirectory(string newDirectory)
{
	_settings->changeSaveDirectory(newDirectory);
}

bool MemoryV2::changeViewType(int newViewType)
{
	return _settings->changeViewType(newViewType);
}

void MemoryV2::resizeWindow()
{
	_settings->resizeWindow();
}
