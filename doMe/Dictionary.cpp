#include "Dictionary.h"

Dictionary* Dictionary::_theOne = NULL;

Dictionary::Dictionary(void)
{
	generateVocabulary();
}

Dictionary::~Dictionary(void)
{
	map<string, SynonymList*>::iterator it;
		for(it = _wordMap.begin(); it != _wordMap.end(); it++) {
		delete it->second;
	}
}

Dictionary* Dictionary::getInstance() {
	if(_theOne == NULL) {
		_theOne = new Dictionary;
	}
	return _theOne;
}

bool Dictionary::hasMeaning(string meaning, string s) {
	vector<string>* synonyms = getSynonyms(meaning);
	return isFoundInVector(synonyms, s);
}

void Dictionary::generateVocabulary() { 
	addV1VocabularyPackage();
	addChronoVocabularyPackage();
}

void Dictionary::addV1VocabularyPackage() {
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

	return;
}

void Dictionary::addChronoVocabularyPackage() {
	addJanuary();
	addFebruary();
	addMarch();
	addApril();
	addMay();
	addJune();
	addJuly();
	addAugust();
	addSeptember();
	addOctober();
	addNovember();
	addDecember();
	addMonthsOfTheYear();
	addMonday();
	addTuesday();
	addWednesday();
	addThursday();
	addFridary();
	addSaturday();
	addSunday();
	addDaysOfTheWeek();
	addTomorrow();
	addToday();
	addYesterday();
	addPM();
	addAM();
	addMeridiem();
	void addFirst();
	void addSecond();
	void addThird();
	void addFourth();
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
	list->add(getSynonyms("DISPLAY"));
	list->add("VIEWTYPE");
	list->add("DISPLAYTYPE");
	list->add("DISPTYPE");
	list->add("VTYPE");
	addToDictionary(list);
}

void Dictionary::addChangeDirectory() {
	SynonymList* list = new SynonymList("CHANGEDIRECTORY");
	list->add(getSynonyms("DIRECTORY"));
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

void Dictionary::addJanuary() {
	SynonymList* list = new SynonymList("JANUARY");
	list->add("JAN");
	list->add("JANUARY");
	addToDictionary(list);
}

void Dictionary::addFebruary()  {
	SynonymList* list = new SynonymList("FEBRUARY");
	list->add("FEB");
	list->add("FEBRUARY");
	addToDictionary(list);
}

void Dictionary::addMarch() {
	SynonymList* list = new SynonymList("MARCH");
	list->add("MARCH");
	list->add("MAR");
	addToDictionary(list);
}

void Dictionary::addApril() {
	SynonymList* list = new SynonymList("APRIL");
	list->add("APR");
	list->add("APRIL");
	addToDictionary(list);
}

void Dictionary::addMay() {
	SynonymList* list = new SynonymList("MAY");
	list->add("MAY");
	addToDictionary(list);
}

void Dictionary::addJune() {
	SynonymList* list = new SynonymList("JUNE");
	list->add("JUNE");
	list->add("JUN");
	addToDictionary(list);
}

void Dictionary::addJuly() {
	SynonymList* list = new SynonymList("JULY");
	list->add("JUL");
	list->add("JULY");
	addToDictionary(list);
}

void Dictionary::addAugust() {
	SynonymList* list = new SynonymList("AUGUST");
	list->add("AUG");
	list->add("AUGUST");
	addToDictionary(list);
}

void Dictionary::addSeptember() {
	SynonymList* list = new SynonymList("SEPTEMBER");
	list->add("SEP");
	list->add("SEPTEMBER");
	addToDictionary(list);
}

void Dictionary::addOctober() {
	SynonymList* list = new SynonymList("OCTOBER");
	list->add("OCTOBER");
	list->add("OCT");
	addToDictionary(list);
}

void Dictionary::addNovember() {
	SynonymList* list = new SynonymList("NOVEMBER");
	list->add("NOVEMBER");
	list->add("NOV");
	addToDictionary(list);
}

void Dictionary::addDecember() {
	SynonymList* list = new SynonymList("DECEMBER");
	list->add("DEC");
	list->add("DECEMBER");
	addToDictionary(list);
}

void Dictionary::addMonthsOfTheYear() {
	SynonymList* list = new SynonymList("MONTHSOFTHEYEAR");
	list->add(getSynonyms("JANUARY"));
	list->add(getSynonyms("FEBRUARY"));
	list->add(getSynonyms("MARCH"));
	list->add(getSynonyms("APRIL"));
	list->add(getSynonyms("MAY"));
	list->add(getSynonyms("JUNE"));
	list->add(getSynonyms("JULY"));
	list->add(getSynonyms("AUGUST"));
	list->add(getSynonyms("SEPTEMBER"));
	list->add(getSynonyms("OCTOBER"));
	list->add(getSynonyms("NOVEMBER"));
	list->add(getSynonyms("DECEMBER"));
	addToDictionary(list);
}

void Dictionary::addMonday() {
	SynonymList* list = new SynonymList("MONDAY");
	list->add("MON");
	list->add("MONDAY");
	addToDictionary(list);
}

void Dictionary::addTuesday() {
	SynonymList* list = new SynonymList("TUESDAY");
	list->add("TUESDAY");
	list->add("TUE");
	list->add("TUES");
	addToDictionary(list);
}

void Dictionary::addWednesday() {
	SynonymList* list = new SynonymList("WEDNESDAY");
	list->add("WED");
	list->add("WEDNESDAY");
	addToDictionary(list);
}

void Dictionary::addThursday() {
	SynonymList* list = new SynonymList("THURSDAY");
	list->add("THUR");
	list->add("THU");
	list->add("THURSDAY");
	list->add("THURS");
	addToDictionary(list);
}

void Dictionary::addFridary() {
	SynonymList* list = new SynonymList("FRIDAY");
	list->add("FRI");
	list->add("FRIDAY");
	addToDictionary(list);
}

void Dictionary::addSaturday() {
	SynonymList* list = new SynonymList("SATURDAY");
	list->add("SAT");
	list->add("SATURDAY");
	addToDictionary(list);
}

void Dictionary::addSunday() {
	SynonymList* list = new SynonymList("SUNDAY");
	list->add("SUN");
	list->add("SUNDAY");
	addToDictionary(list);
}

void Dictionary::addDaysOfTheWeek() {
	SynonymList* list = new SynonymList("DAYSOFTHEWEEK");
	list->add(getSynonyms("MONDAY"));
	list->add(getSynonyms("TUESDAY"));
	list->add(getSynonyms("WEDNESDAY"));
	list->add(getSynonyms("THURSDAY"));
	list->add(getSynonyms("FRIDAY"));
	list->add(getSynonyms("SATURDAY"));
	list->add(getSynonyms("SUNDAY"));
	addToDictionary(list);
}

void Dictionary::addTomorrow() {
	SynonymList* list = new SynonymList("TOMORROW");
	list->add("TMR");
	list->add("TOMORROW");
	addToDictionary(list);
}

void Dictionary::addToday() {
	SynonymList* list = new SynonymList("TODAY");
	list->add("TDAY");
	list->add("TODAY");
	list->add("TDY");
	addToDictionary(list);
}

void Dictionary::addYesterday() {
	SynonymList* list = new SynonymList("YESTERDAY");
	list->add("YSTRDAY");
	list->add("YESTERDAY");
	list->add("YEST");
	addToDictionary(list);
}

void Dictionary::addAM() {
	SynonymList* list = new SynonymList("AM");
	list->add("AM");
	addToDictionary(list);
}

void Dictionary::addPM() {
	SynonymList* list = new SynonymList("PM");
	list->add("PM");
	addToDictionary(list);
}

void Dictionary::addMeridiem() {
		SynonymList* list = new SynonymList("PM");
		list->add(getSynonyms("AM"));
		list->add(getSynonyms("PM"));
		addToDictionary(list);
}

void Dictionary::addFirst() {
		SynonymList* list = new SynonymList("FIRST");
		list->add(getSynonyms("ST"));
		addToDictionary(list);
}
void Dictionary::addSecond() {
		SynonymList* list = new SynonymList("SECOND");
		list->add(getSynonyms("ND"));
		addToDictionary(list);
}

void Dictionary::addThird() {
		SynonymList* list = new SynonymList("THIRD");
		list->add(getSynonyms("RD"));
		addToDictionary(list);
}

void Dictionary::addFourth() {
		SynonymList* list = new SynonymList("FOURTH");
		list->add(getSynonyms("TH"));
		addToDictionary(list);
}

void Dictionary::addToDictionary(SynonymList* list) {
		_wordMap.insert(pair<string, SynonymList*>(
						list->getMeaning(), 
						list));
	return;
}

vector<string>* Dictionary::getSynonyms(string s) {
	map<string, SynonymList*>::iterator found = _wordMap.find(s);
	assert(found != _wordMap.end());
	return found->second->getSynonyms();
}	 

bool Dictionary::isFoundInVector(vector<string>* vector, string s) {
	assert(vector);
	for(unsigned int i = 0; i < vector->size(); i++) {
		if(s.compare((*vector)[i]) == 0) {
			return true;
		}
	}
	return false;
}