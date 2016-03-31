//@@author A0122569B

#pragma once

#include "Dictionary.h"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <assert.h>
#include <cstddef>

#define START_INDEX 0
#define SECOND_INDEX 1
#define NO_STRING ""

using namespace std;

class InputTokens
{
public:
	InputTokens(string commandLine);
	~InputTokens(void);
	
	//An array of methods to allow
	//other classes to analyze and 
	//retrieve the tokens for parsing
	string getToken(int index);			//returns the token used for parsing
	string getOriginalToken(int index);	//returns the original token
	int getInteger(int index);			//returns int value of the token denoted by the index
	unsigned int getSize();				//returns total number of tokens
	unsigned int getSize(int index);	//returns number of characters in the token denoted by the index

	bool isOutOfBounds(int index);				//checks if the index is out of the bounds of the tokens
	bool hasNoMoreWord(int index);				//checks if the there are anymore words to be parsed
	bool hasMeaning(string meaning, int index);	//checks if the token denoted by index has the expected meaning	
	bool isInteger(int index);					//checks if the token is a number					
	bool isParsed(int index);					//checks if a the token has already been processed
	bool isExtensionOfAWord(int index);			//checks if the token is an extension of a word inputted by user
	bool isBreakPoint(int index);				//checkks if the point indicated by index is the end point of a token chain collection
	bool isMarkedAs(string marker, int index);	//checks if the token indicated by index has the same value as marker
	
	void markAs(string marker, int index);
	void markAs(string firstMarker, string secondMarker, int index);
	void remove(int index);

private:
	vector<string> _tokensOriginal;
	vector<string> _tokens;
	Dictionary* _dictionary;
	
	//private method that lexes the commandline passed during construction into tokens
	//the lexing will split the commandline based on white spaces and
	//further splits words into strings of numbers or alphabets
	//there will be 2 sets of tokens, 1 set will contain authentic information about the original command
	//the other will be capitalized to remove case sensitivity and can be marked by lower case letters
	//to indicate that the token's information has been extracted
	void generateTokensFromCommandLine(string commandLine);

	void addToVector(string token, string original);
	vector<string> getTokensFromChunk(string chunk);

	size_t getAlphabets(size_t index, string chunk, vector<string>* tokens);
	size_t getNumbers(size_t index, string chunk, vector<string>*  tokens);
	string makeAllCaps(string s);
	bool isInteger(char c);
	bool isLowerCase(string s);
};