//@@author A0114990A

#pragma once

#include <string>

using namespace std;

class Exception_FileCannotOpen
{
private:
	string _errorMsg;
public:
	Exception_FileCannotOpen(string);
	~Exception_FileCannotOpen();

	string getString();
};

