#include "Parser.h"

Parser::Parser(string commandLine) :
_commandLine(commandLine)
{
}

Parser::~Parser(void) {
}

CommandPackage Parser::parse() {

	getParametersFromCommandLine();
	guessCommandType();
	findDetailsIfSimpleCommandType();
	findDetailsIfNotSimpleCommandType();

	return _commandPackage;
}

void Parser::setCommandLine(string commandLine) {
	_commandLine = commandLine;
	return;
}

CommandPackage Parser::getCommandPackage() {
	return _commandPackage;
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
	case ADD:
		break;
	case EDIT:
		break;
	default:
		break;
	}
	return;
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
	} else if(_commandParameters.size() > 1) {
		_commandType = ADD;
	}
	return;
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

string Parser::makeAllCaps(string s) {
	transform(s.begin(), s.end(), s.begin(), toupper);
	return s;
}

bool Parser::isInteger(string s) {
	return (s.find_first_not_of("1234567890") == std::string::npos);
}