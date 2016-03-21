//Class stores lists of word and its corresponding meaning, object ptrs to be stored in the Dictionary object

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