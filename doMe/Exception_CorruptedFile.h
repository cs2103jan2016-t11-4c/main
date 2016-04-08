//@@author A0125290M
#pragma once
#include <string>
using namespace std;


class Exception_CorruptedFile {
private:
	static const string ERROR_MESSAGE;
public:
	Exception_CorruptedFile();
	string getString();
};