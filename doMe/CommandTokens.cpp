#include "CommandTokens.h"


CommandTokens::CommandTokens(string commandLine) :
	_commandLine(commandLine)
{
	_dictionary = Dictionary::getInstance();
	generateTokensFromCommandLine();
}

CommandTokens::~CommandTokens(void)
{
}

void CommandTokens::generateTokensFromCommandLine() {
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

vector<string> CommandTokens::getTokensFromChunk(string chunk) {
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

size_t CommandTokens::getAlphabets(size_t index, string chunk, vector<string>* tokens) {
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

size_t CommandTokens::getNumbers(size_t index, string chunk, vector<string>*  tokens) {
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

string CommandTokens::makeAllCaps(string s) {
	transform(s.begin(), s.end(), s.begin(), toupper);
	return s;
}

bool CommandTokens::isBlank(int index) {
	assert(!isOutOfBounds(index));
	if(_tokensOriginal[index] == NO_STRING) {
		return true;
	} else {
		return false;
	}
}

void CommandTokens::replaceWith(string s, int index) {
	assert(!isOutOfBounds(index));
	_tokensOriginal[index] = s;
	return;
}

string CommandTokens::getToken(int index) {
	assert(!isOutOfBounds(index));
	return _tokens[index];
}

int CommandTokens::getInteger(int index) {
	assert(!isOutOfBounds(index));
	assert(isInteger(index));
	return stoi(_tokens[index]);
}

string CommandTokens::getOriginalToken(int index) {
	assert(index < _tokens.size());
	assert(index >= 0);
	return _tokensOriginal[index];
}

bool CommandTokens::isOutOfBounds(int index) {
	if(index < 0) {
		return true;
	} else if(index >= _tokens.size()) {
		return true;
	} else {
		return false;
	}
}

bool CommandTokens::hasMeaning(string meaning, int index) {
	assert(index < _tokens.size());
	assert(index >= 0);
	return _dictionary->hasMeaning(meaning, _tokens[index]);
}

bool CommandTokens::noMoreTokens(int index) {
	while(!isOutOfBounds(index) && _tokensOriginal[index] == NO_STRING) {
		index++;
	}
	return isOutOfBounds(index);
}

int CommandTokens::getSize() {
	return _tokens.size();
}

int CommandTokens::getSize(int index) {
	assert(!isOutOfBounds(index));
	return _tokens[index].size();
}

void CommandTokens::remove(int index) {
	assert(!isOutOfBounds(index));
	_tokens.erase(_tokens.begin()+index);
	_tokensOriginal.erase(_tokensOriginal.begin()+index);
	return;
}

bool CommandTokens::isInteger(int index) {
	assert(!isOutOfBounds(index));
	if(_tokens[index].find_first_not_of("1234567890") == string::npos) {
		return true;
	} else {
		return false;
	}
}

bool CommandTokens::isInteger(char c) {
	if(c >= '0' && c <= '9') {
		return true;
	} else {
		return false;
	}
}

bool CommandTokens::isParsed(int index) {
	assert(!isOutOfBounds(index));
	if(_tokens[index] < "a") {
		return false;
	} else {
		return true;
	}
}

bool CommandTokens::isBreakPoint(int index) {
	return isOutOfBounds(index) || isParsed(index);
}

bool CommandTokens::isMarkedAs(string s, int index) {
	assert(!isOutOfBounds(index));
	if(_tokens[index].compare(s) == 0) {
		return true;
	} else {
		return false;
	}
}

void CommandTokens::markAs(string s, int index) {
	assert(!isOutOfBounds(index));
	_tokens[index] = s;
	return;
}