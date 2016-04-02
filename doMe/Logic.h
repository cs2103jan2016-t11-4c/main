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

	stack<Command*> _commandUndoStack;
	stack<Command*> _commandRedoStack;

	Parser* _parser;
	Memory* _memory;

	void executeUndoRedo(Command* command);
	void undo(Command* command);
	void redo(Command* command);
	void clearCommandRedoStack();


	void throwExceptionIfEmpty(string commandText);
public:
	~Logic();
	static Logic* getInstance();
	Command* executeCommand(string commandText);
};