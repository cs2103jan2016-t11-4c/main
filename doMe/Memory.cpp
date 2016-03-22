#include "Memory.h"

Memory* Memory::_instance = 0;

Memory* Memory::getInstance()
{
	if (_instance == 0) {
		_instance = new Memory;
	}
	return _instance;
}

Memory::Memory() 
{
	_settings = Settings::getInstance(); //main functionality from Settings constructor
	_ram = RAM::getInstance();			 //main functionality from RAM constructor
}

void Memory::changeSaveDirectory(string newDirectory)
{
	_settings->changeSaveDirectory(newDirectory);
}

bool Memory::changeViewType(int newViewType)
{
	return _settings->changeViewType(newViewType);
}

void Memory::resizeWindow()
{
	_settings->resizeWindow();
}
