#include "InputTokens.h"


InputTokens::InputTokens(string commandLine) :
	_commandLine(commandLine)
{
	_dictionary = Dictionary::getInstance();
	generateTokensFromCommandLine();
}

InputTokens::~InputTokens(void)
{
}

string InputTokens::getToken(int index) {
	assert(!isOutOfBounds(index));
	return _tokens[index];
}

string InputTokens::getOriginalToken(int index) {
	assert(index < _tokens.size());
	assert(index >= 0);
	return _tokensOriginal[index];
}

int InputTokens::getInteger(int index) {
	assert(!isOutOfBounds(index));
	assert(isInteger(index));
	return stoi(_tokens[index]);
}

int InputTokens::getSize() {
	return _tokens.size();
}

int InputTokens::getSize(int index) {
	assert(!isOutOfBounds(index));
	return _tokens[index].size();
}

bool InputTokens::isOutOfBounds(int index) {
	if(index < 0) {
		return true;
	} else if(index >= _tokens.size()) {
		return true;
	} else {
		return false;
	}
}

bool InputTokens::hasNoMoreWord(int index) {
	while(!isOutOfBounds(index) && _tokensOriginal[index] == NO_STRING) {
		index++;
	}
	return isOutOfBounds(index);
}

bool InputTokens::hasMeaning(string meaning, int index) {
	assert(index < _tokens.size());
	assert(index >= 0);
	return _dictionary->hasMeaning(meaning, _tokens[index]);
}

bool InputTokens::isInteger(int index) {
	assert(!isOutOfBounds(index));
	if(_tokens[index].find_first_not_of("1234567890") == string::npos) {
		return true;
	} else {
		return false;
	}
}

bool InputTokens::isInteger(char c) {
	if(c >= '0' && c <= '9') {
		return true;
	} else {
		return false;
	}
}

bool InputTokens::isParsed(int index) {
	assert(!isOutOfBounds(index));
	if(_tokens[index] < "a") {
		return false;
	} else {
		return true;
	}
}

bool InputTokens::isExtensionOfAWord(int index) {
	assert(!isOutOfBounds(index));
	if(_tokensOriginal[index] == NO_STRING) {
		return true;
	} else {
		return false;
	}
}

bool InputTokens::isBreakPoint(int index) {
	return isOutOfBounds(index) || isParsed(index);
}

bool InputTokens::isMarkedAs(string s, int index) {
	assert(!isOutOfBounds(index));
	if(_tokens[index].compare(s) == 0) {
		return true;
	} else {
		return false;
	}
}

void InputTokens::markAs(string s, int index) {
	assert(!isOutOfBounds(index));
	_tokens[index] = s;
	return;
}

void InputTokens::markAs(string firstString, string secondString, int index) {
	assert(!isOutOfBounds(index));
	_tokens[index] = firstString;
	_tokensOriginal[index] = secondString;
	return;
}

void InputTokens::remove(int index) {
	assert(!isOutOfBounds(index));
	_tokens.erase(_tokens.begin()+index);
	_tokensOriginal.erase(_tokensOriginal.begin()+index);
	return;
}




void InputTokens::generateTokensFromCommandLine() {
	assert(_commandLine.size() > 0);
	istringstream is(_commandLine);
	string chunk;
	while(is >> chunk) {
		vector<string> tokens = getTokensFromChunk(makeAllCaps(chunk));
		_tokens.push_back(tokens[START_INDEX]);
		_tokensOriginal.push_back(chunk);
		for(int i = 1; i < tokens.size(); i++) {
			_tokens.push_back(tokens[i]);
			_tokensOriginal.push_back("");
		}
	}
	return;
}

vector<string> InputTokens::getTokensFromChunk(string chunk) {
	assert(chunk.size() > 0);
	vector<string> tokens;
	size_t index = START_INDEX;
	while(index != string::npos) {
		if(isInteger(chunk[index])) {
			index = getNumbers(index, chunk, &tokens);
		} else {
			index = getAlphabets(index, chunk, &tokens);
		}
	}
	return tokens;
}

size_t InputTokens::getAlphabets(size_t index, string chunk, vector<string>* tokens) {
	assert(index != string::npos);
	assert(tokens != NULL);
	assert(chunk.size() > 0);
	assert(chunk.size() > index);
	size_t next = chunk.find_first_of("0123456789", index);
	if(next != string::npos) {
		tokens->push_back(chunk.substr(index,next-index));
	} else {
		tokens->push_back(chunk.substr(index));
	}
	return next;
}

size_t InputTokens::getNumbers(size_t index, string chunk, vector<string>*  tokens) {
	assert(index != string::npos);
	assert(tokens != NULL);
	assert(chunk.size() > 0);
	assert(chunk.size() > index);
	size_t next = chunk.find_first_not_of("0123456789", index);
	if(next != string::npos) {
		tokens->push_back(chunk.substr(index,next-index));
	} else {
		tokens->push_back(chunk.substr(index));
	}
	return next;
}

string InputTokens::makeAllCaps(string s) {
	transform(s.begin(), s.end(), s.begin(), toupper);
	return s;
}
























