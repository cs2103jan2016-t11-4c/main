//Class stores lists of word and its corresponding meaning, object ptrs to be stored in the Dictionary object
//The class is contructed with a string as its meaning and strings or string vectors can be added to the object
//that have the meaning provided by the meaning string
//Construction requires a string parameter and this string will hold the meaning in the object.
//
//The main API is void add(string)
//Description: adds words that serve as synonyms to the meaning string
//Pre-Condition: Must not be a null string
//Post-Condition: The string is stored in the object's synonym string vector
//The API has 1 overload with void add(vector<string>*);
//
//string getMeaning() and vector<string>* getSynonyms() methods can be used to retrieve 
//the meaning and list of synonyms
//
//@@author A0122569B

#pragma once

#include <vector>
#include <string>
#include <assert.h>

using namespace std;

class SynonymList
{
public:
	SynonymList(string meaning);
	~SynonymList(void);

	string getMeaning();
	vector<string>* getSynonyms();
	void add(string synonym);
	void add(vector<string>* synonyms);

private:
	vector<string>* _synonyms;
	string _meaning;
};