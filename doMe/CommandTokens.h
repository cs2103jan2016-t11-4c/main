#pragma once
#include "Dictionary.h"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <assert.h>
#include <cstddef>

#define START_INDEX 0
#define NO_STRING ""

using namespace std;

class CommandTokens
{
public:
	CommandTokens(string commandLine);
	~CommandTokens(void);

private:
	string _commandLine;
	vector<string> _tokensOriginal;
	vector<string> _tokens;
	Dictionary* _dictionary;

public:
	void generateTokensFromCommandLine();

	vector<string> getTokensFromChunk(string chunk);
	size_t getAlphabets(size_t index, string chunk, vector<string>* tokens);
	size_t getNumbers(size_t index, string chunk, vector<string>*  tokens);
	string makeAllCaps(string s);	

	bool isBlank(int index);
	void replaceWith(string s, int index);
	string getToken(int index);
	int getInteger(int index);
	string getOriginalToken(int index);
	bool isOutOfBounds(int index);
	bool hasMeaning(string meaning, int index);
	bool noMoreTokens(int index);
	int getSize();
	int getSize(int index);
	void remove(int index);

	bool isInteger(int index);
	bool isInteger(char c);
	bool isParsed(int index);
	bool isBreakPoint(int index);
	bool isMarkedAs(string s, int index);

	void markAs(string s, int index);
};