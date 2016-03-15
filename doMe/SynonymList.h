#pragma once
#include <vector>
#include <string>
#include <assert.h>

using namespace std;

class SynonymList
{
private:
	vector<string>* _synonyms;
	string _meaning;

public:
	SynonymList(string meaning);
	~SynonymList(void);

	void add(string synonym);
	void add(vector<string>* synonyms);
	string getMeaning();
	vector<string>* getSynonyms();
};

