//Dictionary stores list of words and their corresponding meaning.
//This singleton class is to be initialized with the getInstance() method which returns a ptr to the object
//The main API is bool Dictionary::hasMeaning(string meaning, string s);
//Description: checks if a certain string s has the meaning provided by the meaning string
//Pre-Condition: The meaning string is already in the dictionary
//Post-Condition: None
//
//@@author A0122569B

#pragma once

#include "SynonymList.h"
#include "Commons.h"
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

	vector<string>* getSynonyms(string s);		//string must be present in dictionary
	void addToDictionary(SynonymList* list);	//method that adds words to the dictionary

private:
	Dictionary(void);
	
	static Dictionary* _theOne;
	map<string, SynonymList*> _wordMap;

	void generateVocabulary();	//new vocabulary to be added through this method

	void addBasicVocabularyPackage();
	void addChronoVocabularyPackage();
	void addNaturalLanguagePackage();

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
	void addDate();
	void addLocation();
	void addTime();
	void addDeleteParameter();
	void addDone();
	void addUndone();
	void addRedo();
	void addHelp();

	void addHrs();
	void addDateDivider();
	void addTimeDivider();
	void addJanuary();
	void addFebruary();
	void addMarch();
	void addApril();
	void addMay();
	void addJune();
	void addJuly();
	void addAugust();
	void addSeptember();
	void addOctober();
	void addNovember();
	void addDecember();
	void addMonthsOfTheYear();
	void addMonday();
	void addTuesday();
	void addWednesday();
	void addThursday();
	void addFridary();
	void addSaturday();
	void addSunday();
	void addDaysOfTheWeek();
	void addWeek();
	void addTomorrow();
	void addToday();
	void addYesterday();
	void addRelationalDate();
	void addAM();
	void addPM();
	void addMeridiem();
	void addFirst();
	void addSecond();
	void addThird();
	void addFourth();
	void addNumberSuffix();
	void addRange();
	
	void addNext();
	void addThis();
	void addTo();
	void addBy();
	void addFrom();
	void addOn();
	void addDue();
	void addPreposition();
	void addFor();
	void addThe();
	void addAll();
	void addNot();

	bool isFoundInVector(vector<string>* vector, string s);
};