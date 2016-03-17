#pragma once

#include "Command.h"
#include <string>

using namespace std;

class Parser_Interface
{
public:
	Parser_Interface(void);
	~Parser_Interface(void);
	virtual void setCommandLine(string newCommandLine)=0;
	virtual Command* getCommand()=0;
};