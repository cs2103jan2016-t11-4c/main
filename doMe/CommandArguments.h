#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <assert.h>

using namespace std;

class CommandArguments
{
public:
	CommandArguments(string commandLine);
	~CommandArguments(void);

private:
	string _commandLine;
	vector<string> _caseSensitiveArguments;
	vector<string> _arguments;

public:
	void getParametersFromCommandLine();
	string makeAllCaps(string s);
	vector<string> splitSentence(string sentence);

	string getArgument(int index);
	bool isOutOfBounds(int index);

};



