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

class InputTokens
{
public:
	InputTokens(string commandLine);
	~InputTokens(void);
	
	string getToken(int index);			//returns the token used for parsing
	string getOriginalToken(int index);	//returns the original token
	int getInteger(int index);			//returns int value of the token denoted by the index
	int getSize();						//returns total number of tokens
	int getSize(int index);				//returns number of characters in the token denoted by the index

	bool isOutOfBounds(int index);				//checks if the index is out of the bounds of the tokens
	bool hasNoMoreWord(int index);
	bool hasMeaning(string meaning, int index);	//checks if the token denoted by index has the expected meaning	
	bool isInteger(int index);					//checks if the token is a number
	bool isInteger(char c);						//checks if a character is a number					
	bool isParsed(int index);					//checks if a the token has already been processed
	bool isExtensionOfAWord(int index);			//checks if the token is an extension of a word inputted by user
	bool isBreakPoint(int index);
	bool isMarkedAs(string s, int index);	

	void markAs(string s, int index);
	void markAs(string firstString, string secondString, int index);
	void remove(int index);

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
};