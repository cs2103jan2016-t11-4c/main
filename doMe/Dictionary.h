//Dictionary stores list of words and their corresponding meaning.
//This singleton class is to be initialized with the getInstance() method which return a ptr to the object
//The main API is bool Dictionary::hasMeaning(string meaning, string s);
//Description: checks if a certain string s has the meaning provided by the meaning string
//Pre-Condition: The meaning string is already in the dictionary
//Post-Condition: None

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
	static Dictionary* getInstance();			//method to get pointer to the singleton object

	bool hasMeaning(string meaning, string s);	//returns true if string s has the expected meaning, false otherwise
	~Dictionary(void);

private:
	Dictionary(void);
	
	static Dictionary* _theOne;
	map<string, SynonymList*> _wordMap;

	void generateVocabulary();	//new vocabulary to be added through this method

	void addDirectory();		//methods that add vocabulary to the dictionary
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
	
	vector<string>* getSynonyms(string s);					//string must be present in dictionary
	bool isFoundInVector(vector<string>* vector, string s);
};