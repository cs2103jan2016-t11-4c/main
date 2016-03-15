#include "Dictionary.h"

Dictionary* Dictionary::_theOne = NULL;

bool Dictionary::hasMeaning(string meaning, string s) {
	vector<string>* synonyms = getSynonyms(meaning);
	return isFoundInVector(synonyms, s);
}

vector<string>* Dictionary::getSynonyms(string s) {
	map<string, vector<string>*>::iterator found = _wordMap.find(s);
	assert(found != _wordMap.end());
	return found->second;
}

Dictionary::Dictionary(void)
{
	generateVocabulary();
}

Dictionary::~Dictionary(void)
{
	for(int i=0; i < _vocabulary.size(); i++) {
		delete _vocabulary[i];
	}
}

Dictionary* Dictionary::getInstance() {
	if(_theOne == NULL) {
		_theOne = new Dictionary;
	}
	return _theOne;
}

void Dictionary::generateVocabulary() {
	addDisplay();
	addDirectory();
	addDelete();
	addEdit();
	addClear();
	addUndo();
	addSearch();
	addExit();
	addView();
	addChangeDirectory();
	addChangeViewType();
	addHrs();
	addDivider();	
}

void Dictionary::addDisplay() {
	SynonymList* list = new SynonymList("DISPLAY");
	list->add("V");
	list->add("DISP");
	list->add("DISPLAY");
	list->add("VIEW");
	addToDictionary(list);
}

void Dictionary::addDirectory() {
	SynonymList* list = new SynonymList("DIRECTORY");
	list->add("DIRECTORY");
	list->add("DIR");
	list->add("D");
	addToDictionary(list);
}

void Dictionary::addDelete() {
	SynonymList* list = new SynonymList("DEL");
	list->add("D");
	list->add("DELETE");
	list->add("DEL");
	addToDictionary(list);
}

void Dictionary::addEdit() {
	SynonymList* list = new SynonymList("EDIT");
	list->add("E");
	list->add("ED");
	list->add("CHANGE");
	list->add("C");
	list->add("CHNG");
	list->add("EDIT");
	addToDictionary(list);
}

void Dictionary::addClear() {
	SynonymList* list = new SynonymList("CLEAR");
	list->add("CLEAR");
	list->add("CLR");
	addToDictionary(list);
}

void Dictionary::addUndo() {
	SynonymList* list = new SynonymList("UNDO");
	list->add("U");
	list->add("UNDO");
	list->add("REVERT");
	addToDictionary(list);
}

void Dictionary::addSearch() {
	SynonymList* list = new SynonymList("SEARCH");
	list->add("SEARCH");
	list->add("SRCH");
	list->add("S");
	addToDictionary(list);
}

void Dictionary::addExit() {
	SynonymList* list = new SynonymList("EXIT");
	list->add("EX");
	list->add("EXIT");
	list->add("CLOSE");
	addToDictionary(list);
}

void Dictionary::addView() {
	SynonymList* list = new SynonymList("VIEW");
	list->add(_wordMap.find("DISPLAY")->second);
	list->add("VIEWTYPE");
	list->add("DISPLAYTYPE");
	list->add("DISPTYPE");
	list->add("VTYPE");
	addToDictionary(list);
}

void Dictionary::addChangeDirectory() {
	SynonymList* list = new SynonymList("CHANGEDIRECTORY");
	list->add(_wordMap.find("DIRECTORY")->second);
	list->add("CD");
	list->add("CDIRECTORY");
	list->add("CDIR");
	list->add("CHANGEDIR");
	list->add("CHANGEDIRECTORY");
	list->add("CHNGD");
	list->add("CHNGDIR");
	list->add("CHNGDIRECTORY");
	addToDictionary(list);
}

void Dictionary::addChangeViewType() {
	SynonymList* list = new SynonymList("CHANGEVIEWTYPE");
	list->add("VIEW");
	list->add("CV");
	list->add("CVIEW");
	list->add("CDISPLAY");
	list->add("CDISP");
	list->add("CHNGVIEW");
	list->add("CHNGV");
	list->add("CHNGDISPLAY");
	list->add("CHNGDISP");
	list->add("CHANGEV");
	list->add("CHANGEVIEW");
	list->add("CHANGEDISPLAY");
	list->add("CHANGEDISP");
	list->add("VIEWTYPE");
	addToDictionary(list);
}

void Dictionary::addHrs() {
	SynonymList* list = new SynonymList("HRS");
	list->add("HRS");
	addToDictionary(list);
}

void Dictionary::addDivider() {
	SynonymList* list = new SynonymList("DIVIDER");
	list->add("/");
	list->add("-");
	addToDictionary(list);
}

void Dictionary::addToDictionary(SynonymList* list) {
	addToVocabulary(list);
	addToMap(list);
	return;
}

void Dictionary::addToVocabulary(SynonymList* list) {
	_vocabulary.push_back(list);
	return;
}

void Dictionary::addToMap(SynonymList* list) {
	_wordMap.insert(pair<string, vector<string>*>(
					list->getMeaning(), 
					list->getSynonyms()));
	return;
}

bool Dictionary::isFoundInVector(vector<string>* vector, string s) {
	for(int i=0; i < vector->size(); i++) {
		if(s.compare((*vector)[i])==0) {
			return true;
		}
	}
	return false;
}