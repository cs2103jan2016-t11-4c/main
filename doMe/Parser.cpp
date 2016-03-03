#include "Parser.h"

Parser::Parser(string commandLine) :
_commandLine(commandLine)
{
}

Parser::~Parser(void) {
}

CommandPackage* Parser::parse() {

	getParametersFromCommandLine();
	guessCommandType();
	findDetailsIfSimpleCommandType();
	findDetailsIfNotSimpleCommandType();
	parseAsAddCommandIfStillNotParsed();

	return &_commandPackage;
}

void Parser::setCommandLine(string commandLine) {
	_commandLine = commandLine;
	return;
}

CommandPackage* Parser::getCommandPackage() {
	return &_commandPackage;
}

void Parser::getParametersFromCommandLine() {
	_caseSensitiveCommandParameters = splitSentence(_commandLine);
	_commandLine = makeAllCaps(_commandLine);
	_commandParameters = splitSentence(_commandLine);
	return;
}

void Parser::guessCommandType() {
	if(isAdd(_commandParameters[COMMAND_POSITION])) {
		_commandType = ADD;
	} else if(isDisplay(_commandParameters[COMMAND_POSITION])) {
		_commandType = DISPLAY;
	} else if(isDelete(_commandParameters[COMMAND_POSITION])) {
		_commandType = DELETE;
	} else if(isEdit(_commandParameters[COMMAND_POSITION])) {
		_commandType = EDIT;
	} else if(isClear(_commandParameters[COMMAND_POSITION])) {
		_commandType = CLEAR;
	} else if(isUndo(_commandParameters[COMMAND_POSITION])) {
		_commandType = UNDO;
	} else if(isSort(_commandParameters[COMMAND_POSITION])) {
		_commandType = SORT;
	} else if(isSearch(_commandParameters[COMMAND_POSITION])) {
		_commandType = SEARCH;
	} else if(isViewType(_commandParameters[COMMAND_POSITION])) {
		_commandType = VIEWTYPE;
	} else if(isSaveDirectory(_commandParameters[COMMAND_POSITION])) {
		_commandType = SAVEDIRECTORY;
	} else if(isExit(_commandParameters[COMMAND_POSITION])) {
		_commandType = EXIT;
	} else {
		_commandType = ADD;
	}
}

void Parser::findDetailsIfSimpleCommandType() {
	switch(_commandType) {
	case DISPLAY:
		packCommandIfConfirmedDisplayCommand();
		break;
	
	case DELETE:
		packCommandIfConfirmedDeleteCommand();
		break;
	
	case UNDO:
		packCommandIfConfirmedUndoCommand();
		break;
	
	case SORT:
		packCommandIfConfirmedSortCommand();
		break;
	
	case SAVEDIRECTORY:
		packCommandIfConfirmedSavedDirectoryCommand();
		break;
	
	case EXIT:
		packCommandIfConfirmedExitCommand();
		break;
	
	default:
		break;
	}
}

void Parser::findDetailsIfNotSimpleCommandType() {
	switch(_commandType) {
	case EDIT:
		packCommandIfConfirmedEditCommand();
		break;
	case CLEAR:
		packCommandIfConfirmedClearCommand();
		break;
	case SEARCH:
		packCommandIfConfirmedSearchCommand();
	break;
	case VIEWTYPE:
		packCommandIfConfirmedViewTypeCommand();
		break;
	default:
		break;
	}
	return;
}

void Parser::parseAsAddCommandIfStillNotParsed() {
	if(_commandType == ADD) {
	removeAddCommand();
	getDateAndTimeParameters();
	getLocationParameter();
	getDescriptionParameter();
	packAddCommand();
	}
}

bool Parser::isAdd(std::string s) {
	if(s.compare("ADD") == 0) {
		return true;
	} else if(s.compare("A") == 0) {
		return true;
	} else {
		return false;
	}
}

bool Parser::isDisplay(std::string s) {
	if(s.compare("DISPLAY") == 0) {
		return true;
	} else if(s.compare("VIEW") == 0) {
		return true;
	} else if(s.compare("V") == 0) {
		return true;
	} else {
		return false;
	}
}

bool Parser::isDelete(std::string s) {
	if(s.compare("DELETE") == 0) {
		return true;
	} else if(s.compare("D") == 0) {
		return true;
	} else {
		return false;
	}
}

bool Parser::isEdit(string s) {
	if(s.compare("EDIT") == 0) {
		return true;
	} else if(s.compare("E") == 0) {
		return true;
	} else {
		return false;
	}
}

bool Parser::isClear(string s) {
	if(s.compare("CLEAR") == 0) {
		return true;
	} else if(s.compare("CLR") == 0) {
		return true;
	} else {
		return false;
	}
}

bool Parser::isUndo(string s) {
	if(s.compare("UNDO") == 0) {
		return true;
	} else if(s.compare("U") == 0) {
		return true;
	} else {
		return false;
	}
}

bool Parser::isSort(string s) {
	if(s.compare("SORT") == 0) {
		return true;
	} else if(s.compare("S") == 0) {
		return true;
	} else {
		return false;
	}
}

bool Parser::isSearch(string s) {
	if(s.compare("SEARCH") == 0) {
		return true;
	} else {
		return false;
	}
}

bool Parser::isViewType(string s) {
	if(s.compare("VIEWTYPE") == 0) {
		return true;
	} else {
		return false;
	}
}

bool Parser::isSaveDirectory(string s) {
	if(s.compare("CHANGE") == 0) {
		return true;
	} else if(s.compare("CD") == 0) {
		return true;
	} else if(s.compare("C") == 0) {
		return true;
	} else {
		return false;
	}
}

bool Parser::isDirectory(string s) {
	if(s.compare("DIRECTORY") == 0) {
		return true;
	} else if(s.compare("D") == 0) {
		return true;
	} else {
		return false;
	}
}

bool Parser::isExit(std::string s) {
	if(s.compare("EXIT") == 0) {
		return true;
	} else if(s.compare("EX") == 0) {
		return true;
	} else {
		return false;
	}
}

void Parser::packCommandIfConfirmedDisplayCommand() {
	if(_commandParameters.size() == 1) {
		_commandPackage = CommandPackage(DISPLAY);
	} else if((_commandParameters.size() == 2) && (isInteger(_commandParameters[INDEX_POSITION]))) {
		_commandType = VIEWTYPE;
	} else if(_commandParameters.size() > 2) {
		_commandType = ADD;
	}
	return;
}

//more details can be extracted
void Parser::packCommandIfConfirmedDeleteCommand() {
	if(_commandParameters.size() == 1) {
		_commandType = INVALID;
	} else if(isInteger(_commandParameters[INDEX_POSITION])) {
		int index = stoi(_commandParameters[INDEX_POSITION]);
		_commandPackage = CommandPackage(DELETE, Task(), index);
	}
}

void Parser::packCommandIfConfirmedUndoCommand() {
	if(_commandParameters.size() == 1) {
		_commandPackage = CommandPackage(UNDO);
	} else if(_commandParameters.size() > 1) {
		_commandType = ADD;
	}
	return;
}

//not done
void Parser::packCommandIfConfirmedSortCommand() {
}

void Parser::packCommandIfConfirmedSavedDirectoryCommand() {
	if((_commandParameters[COMMAND_POSITION].compare("CD") == 0)) {
		if(_commandParameters.size() == 2) {
			_commandPackage = CommandPackage(SAVEDIRECTORY,_caseSensitiveCommandParameters[FIRST_PARAMETER_POSITION]);
		} else if(_commandParameters.size() > 2) {
			_commandType = ADD;
		}
	} else if(_commandParameters.size() == 3) {
		if(isDirectory(_commandParameters[FIRST_PARAMETER_POSITION])) {
			_commandPackage = CommandPackage(SAVEDIRECTORY,_caseSensitiveCommandParameters[FIRST_PARAMETER_POSITION]);
		}
		else if((isViewType(_commandParameters[FIRST_PARAMETER_POSITION])) ||
				(isDisplay(_commandParameters[FIRST_PARAMETER_POSITION]))) {
			_commandType = VIEWTYPE;
		}
	} else if(_commandParameters.size() < 3) {
		_commandType = EDIT;
	}
}

void Parser::packCommandIfConfirmedExitCommand() {
	if(_commandParameters.size() == 1) {
		_commandPackage = CommandPackage(EXIT);
	}
	else {
		_commandType = ADD;
	}
	return;
}

void Parser::packCommandIfConfirmedEditCommand() {
	if(_commandParameters.size() == 1) {
		_commandType = INVALID;
	} else if(isInteger(_commandParameters[INDEX_POSITION])) {
	removeEditCommand();
	getDateAndTimeParameters();
	getLocationParameter();
	getDescriptionParameter();
	packEditCommand();
	} else {
		_commandType = ADD;
	}
	return;
}

void Parser::packEditCommand() {
	if(!finalizeDates()) {
		return;
	} else if(!finalizeTimes()) {
		return;
	} else {
		string location = combineWords(_location);
		string description = combineWords(_description);
		_commandPackage = CommandPackage(EDIT, Task(description, _date1, _date2, _time1, _time2, location));
	}
}

void Parser::packCommandIfConfirmedClearCommand() {
	if(_commandParameters.size() == 1) {
		_commandPackage = CommandPackage(CLEAR);
	}
	else {
		_commandType = ADD;
	}
	return;
}

//not done
void Parser::packCommandIfConfirmedSearchCommand() {
}

void Parser::packCommandIfConfirmedViewTypeCommand() {
	for(int i = 0; i < _commandParameters.size(); i++)
	{
		if(isInteger(_commandParameters[i])) {
			_commandPackage = CommandPackage(VIEWTYPE, Task(), stoi(_commandParameters[i]));
			return;
		}
	}
	_commandType=ADD;
}

void Parser::packAddCommand() {
	if(_description.size() == 0) {
		return;
	} else {
		if(!finalizeDates()) {
			return;
		} else if(!finalizeTimes()) {
			return;
		} else {
			string location = combineWords(_location);
			string description = combineWords(_description);
			_commandPackage = CommandPackage(ADD, Task(description, _date1, _date2, _time1, _time2, location));
		}
	}
}

void Parser::removeAddCommand() {
	if(isAdd(_commandParameters[0])) {
		_commandParameters[0] = "add";
	}
	return;
}

void Parser::removeEditCommand() {
	if(isEdit(_commandParameters[0])) {
		_commandParameters[0] = "edit";
	}
	if(isInteger(_commandParameters[1])) {
		_commandParameters[1] = "index";
	}
	return;
}

void Parser::getDateAndTimeParameters() {
	for(int i=0; i < _commandParameters.size(); i++) {
		if(isInteger(_commandParameters[i])) {
			int value = stoi(_commandParameters[i]);
			if(isTime(value)) {
				_times.push_back(value);
				_commandParameters[i] = "time";
			} else if(isDate(value)) {
				_dates.push_back(value);
				_commandParameters[i] = "date";
			}
		}
	}
	return;
}

bool Parser::finalizeDates() {
	if(_dates.size() > 2) {
		return false;
	} else if(_dates.size() == 0) {
		_date2 = 0;
		_date1 = 0;
	} else if(_dates.size() == 1) {
		_date2 = _dates[0];
		_date1 = 0;
	} else if(_dates.size() == 2) {
		_date1 = _dates[0];
		_date2 = _dates[1];
	}
	return true;
}

bool Parser::finalizeTimes() {
	if(_times.size() > 2) {
		return false;
	} else if(_times.size() == 0) {
		_time2 = -1;
		_time1 = -1;
	} else if(_times.size() == 1) {
		_time2 = _times[0];
		_time1 = -1;
	} else if(_times.size() == 2) {
		_time1 = _times[0];
		_time2 = _times[1];
	}
	return true;
}

void Parser::getLocationParameter() {
	for(int i=0; i < _commandParameters.size(); i++) {
		if(hasLocationMarker(_commandParameters[i])) {
			while((_commandParameters[i] < "a") && i < _commandParameters.size()) {
			_location.push_back(_caseSensitiveCommandParameters[i]);
			i++;
			break;
			}
		}
	}
}

void Parser::getDescriptionParameter() {
	for(int i=0; i < _commandParameters.size(); i++) {
		while((_commandParameters[i] < "a") && i < _commandParameters.size()) {
			_description.push_back(_caseSensitiveCommandParameters[i]);
			i++;
			break;
		}
	}
}

vector<string> Parser::splitSentence(string sentence) {
	istringstream is(sentence);
	vector<string> wordVector;
	string word;

	while(is >> word) {
		wordVector.push_back(word);
	}

	return wordVector;
}

string Parser::combineWords(vector<string> words) {
	std::string sentence;
	for(int i = 0; i < words.size(); i++) {
		sentence = sentence + words[i];
		if(i != words.size() - 1) {
			sentence = sentence + " ";
		}
	}
	return sentence;
}

string Parser::makeAllCaps(string s) {
	transform(s.begin(), s.end(), s.begin(), toupper);
	return s;
}

bool Parser::isInteger(string s) {
	return (s.find_first_not_of("1234567890") == std::string::npos);
}

bool Parser::isTime(int n) {
	if(n/10000 == 0) {
		return true;
	} else { 
		return false;
	}
}

bool Parser::isDate(int n) {
	if(n/100000000 == 0) {
		if(n/10000 != 0) { 
			return true;
		} else {
			return false;
		}
	} else { 
		return false;
	}
}

bool Parser::hasLocationMarker(string s) {
	if(s[0] == '@') {
		return true;
	} else {
		return false;
	}
}