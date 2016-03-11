#include "CommandArguments.h"


CommandArguments::CommandArguments(string commandLine) :
	_commandLine(commandLine)
{
	_caseSensitiveArguments = splitSentence(_commandLine);
	_arguments = splitSentence(makeAllCaps(_commandLine));
}

CommandArguments::~CommandArguments(void)
{
}

vector<string> CommandArguments::splitSentence(string sentence) {
	istringstream is(sentence);
	vector<string> wordVector;
	string word;

	while(is >> word) {
		wordVector.push_back(word);
	}

	return wordVector;
}

string CommandArguments::makeAllCaps(string s) {
	transform(s.begin(), s.end(), s.begin(), toupper);
	return s;
}

string CommandArguments::getArgument(int index) {
	assert(index < _arguments.size());
	return _arguments[index];
}

bool CommandArguments::isOutOfBounds(int index) {
	if(index < 0) {
		return true;
	} else if(index >= _arguments.size()) {
		return true;
	} else {
		return false;
	}
}