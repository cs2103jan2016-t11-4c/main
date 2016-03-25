//@@author A0125290M
#include <iostream>
#include <string>
#include <stack>
#include <assert.h>
#include "Parser.h"
#include "Memory.h"
#include "Command.h"
#include "Commons.h"

using namespace std;

class Logic { 
private:
	static Logic* _instance;
	Logic();

	stack<Command*>* _commandHistoryList;
	Parser* _parser;
	Memory* _memory;

	Command* undo();

public:
	~Logic();
	static Logic* getInstance();
	Command* executeCommand(string commandText);
};