#pragma once
#include "SynonymList.h"
#include <map>
#include <string>
#include <vector>
#include <assert.h>

using namespace std;

class Dictionary
{
public:
	static Dictionary* getInstance();
	vector<string>* getSynonyms(string s);
	bool hasMeaning(string meaning, string s);

private:
	Dictionary(void);
	
	static Dictionary* _theOne;
	map<string, vector<string>*> _wordMap;
	vector<SynonymList*> _vocabulary;

public:
	~Dictionary(void);
	void generateVocabulary();

	void addDirectory();		
	void addDisplay();
	void addDelete();
	void addEdit();
	void addClear();
	void addUndo();
	void addSearch();
	void addExit();
	void addView();
	void addChangeDirectory();
	void addChangeViewType();	
	void addHrs();
	void addDivider();	
	void addToDictionary(SynonymList* list);
	void addToVocabulary(SynonymList* list);
	void addToMap(SynonymList* list);

	bool isFoundInVector(vector<string>* vector, string s);
};

