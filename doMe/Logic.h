//@@author A0125290M
#pragma once
#include <iostream>
#include <string>
#include <stack>
#include <assert.h>
#include "Parser.h"
#include "Command.h"
#include "Commons.h"

using namespace std;

class Logic { 
private:
	Logic();
	static Logic* _instance;
	Parser* _parser;
	stack<Command*> _commandUndoStack;
	stack<Command*> _commandRedoStack;

	static const string LOG_MESSAGE_PARSER;

	bool isUndoOrRedo(Command* command);
	void executeUndoRedo(Command* command);
	void executeNormal(Command* command);
	void undo(Command* command);
	void redo(Command* command);
	void clearCommandRedoStack();
	void throwExceptionIfEmpty(string commandText);
	bool isBlank(string commandText);
public:
	static Logic* getInstance();

	Command* executeCommand(string commandText);
};