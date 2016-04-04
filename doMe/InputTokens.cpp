//@@author A0122569B

#include "InputTokens.h"

InputTokens::InputTokens(string commandLine) {
	_dictionary = Dictionary::getInstance();
	generateTokensFromCommandLine(commandLine);
}

InputTokens::~InputTokens(void) {
}

string InputTokens::getToken(int index) {
	assert(!isOutOfBounds(index));
	
	return _tokens[index];
}

string InputTokens::getOriginalToken(int index) {
	assert(!isOutOfBounds(index));
	
	return _tokensOriginal[index];
}

int InputTokens::getInteger(int index) {
	assert(!isOutOfBounds(index));
	assert(isInteger(index));
	
	return stoi(_tokens[index]);
}

unsigned int InputTokens::getSize() {
	return _tokens.size();
}

unsigned int InputTokens::getSize(int index) {
	assert(!isOutOfBounds(index));
	
	return _tokens[index].size();
}


bool InputTokens::isOutOfBounds(int index) {
	if(index < 0) {
		return true;
	}

	unsigned int positiveIndex = index;
	
	return (positiveIndex >= _tokens.size());
}

bool InputTokens::hasNoMoreWord(int index) {
	while(!isOutOfBounds(index) && _tokensOriginal[index] == NO_STRING) {
		index++;
	}
	
	return isOutOfBounds(index);
}

bool InputTokens::hasMeaning(string meaning, int index) {
	assert(!isOutOfBounds(index));
	
	return _dictionary->hasMeaning(meaning, _tokens[index]);
}

bool InputTokens::isInteger(int index) {
	assert(!isOutOfBounds(index));

	return (_tokens[index].find_first_not_of("1234567890") == string::npos);
}

bool InputTokens::isParsed(int index) {
	assert(!isOutOfBounds(index));
	
	return !(_tokens[index] < "a");
}

bool InputTokens::isExtensionOfAWord(int index) {
	assert(!isOutOfBounds(index));
	
	return (_tokensOriginal[index] == NO_STRING);
}

bool InputTokens::isBreakPoint(int index) {
	return isOutOfBounds(index) || isParsed(index);
}

bool InputTokens::isMarkedAs(string marker, int index) {
	assert(!isOutOfBounds(index));
	
	return (_tokens[index].compare(marker) == 0);
}


void InputTokens::markAs(string marker, int index) {
	assert(!isOutOfBounds(index));
	assert(isLowerCase(marker));

	_tokens[index] = marker;
	
	return;
}

void InputTokens::markAs(string firstMarker, string secondMarker, int index) {
	assert(!isOutOfBounds(index));
	assert(isLowerCase(firstMarker));
	
	_tokens[index] = firstMarker;
	_tokensOriginal[index] = secondMarker;
	
	return;
}

void InputTokens::remove(int index) {
	assert(!isOutOfBounds(index));
	
	_tokens.erase(_tokens.begin()+index);
	_tokensOriginal.erase(_tokensOriginal.begin()+index);
	
	return;
}


void InputTokens::generateTokensFromCommandLine(string commandLine) {
	assert(commandLine.size() != 0);
	
	istringstream is(commandLine);
	string chunk;
	while(is >> chunk) {
		//words starting with * are ignored from parsing
		if(chunk[START_INDEX] == '*') {
			chunk.erase(chunk.begin());
			addToVector(IGNORE_MARKER, chunk);
		} else {
			//if a word contains alphabets and numbers, this function split them to get the tokens
			vector<string> tokens = getTokensFromChunk(makeAllCaps(chunk));
			assert(tokens.size() != 0);
		
			addToVector(tokens[START_INDEX], chunk);
			for(unsigned int i = 1; i < tokens.size(); i++) {
				addToVector(tokens[i], NO_STRING);
			}
		}
	}

	return;
}


void InputTokens::addToVector(string token, string original) {
	_tokens.push_back(token);
	_tokensOriginal.push_back(original);

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
	
	size_t next = chunk.find_first_of("0123456789-/:.", index);
	if(next == index) {
	} else if(next != string::npos) {
		tokens->push_back(chunk.substr(index,next-index));
	} else {
		tokens->push_back(chunk.substr(index));
	}
	
	if(next != string::npos && next == chunk.find_first_of("-/:.", index)) {
		tokens->push_back(chunk.substr(next,1));
		next++;
		if(next >= chunk.size()) {
			next = string::npos;
		}
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

bool InputTokens::isInteger(char c) {
	return (c >= '0' && c <= '9');
}

bool InputTokens::isLowerCase(string s) {
	assert(s.size() != 0);

	return (s.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890") == string::npos);
}