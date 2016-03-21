#include "SynonymList.h"

SynonymList::SynonymList(string meaning) :
_meaning(meaning)
{
	_synonyms = new vector<string>;
}

SynonymList::~SynonymList() {
	delete _synonyms;
}

string SynonymList::getMeaning() {
	return _meaning;
}

vector<string>* SynonymList::getSynonyms() {
	return _synonyms;
}

void SynonymList::add(string synonym)  {
	assert(synonym.compare("") != 0);
	_synonyms->push_back(synonym);
	return;
}

void SynonymList::add(vector<string>* synonyms) {
	assert(synonyms);
	vector<string>& synonymsRef = *synonyms;
	
	for(unsigned int i = 0; i < synonyms->size(); i++) {
		_synonyms->push_back(synonymsRef[i]);
	}
	return;
}