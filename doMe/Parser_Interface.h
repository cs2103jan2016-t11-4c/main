//The interface for the Parser Class
//
//@@author A0122569B

#pragma once

#include "Command.h"
#include <string>

using namespace std;

class Parser_Interface
{
public:
	Parser_Interface(void);
	~Parser_Interface(void);
	virtual Command* parse(string newCommandLine) = 0;
};