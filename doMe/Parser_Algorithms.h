#pragma once

#include "Command.h"
#include "CommandTokens.h"
#include "Parser_Tasks.h"
#include "Task.h"
#include <string>
#include <assert.h>
#include <vector>

#define LAST_INDEX -1
#define NO_STRING ""
#define NO_TASK Task()

using namespace std;

class Parser_Algorithms
{
public:
	Parser_Algorithms(CommandTokens* tokens);
	~Parser_Algorithms(void);
	
	Command* parse();

private:
	CommandTokens* _tokens;
	int _singleIndex;
	vector<int> _indexes;
	string _description;
	Task _task;
	Command _command;

public:
	void initializeAttributes();
	void branchToNodes(int index);

	void nodeOneOfDisplayCommand(int index);
	void nodeTwoOfDisplayCommand(int index);

	void nodeOneOfChangeDirectoryCommand(int index);
	void nodeTwoOfChangeDirectoryCommand(int index);
	void nodeThreeOfChangeDirectoryCommand(int index);

	void nodeOneOfChangeViewTypeCommand(int index);
	void nodeTwoOfChangeViewTypeCommand(int index);
	void nodeThreeOfChangeViewTypeCommand(int index);

	void nodeOneOfDeleteCommand(int index);
	void nodeTwoOfDeleteCommand(int index);	

	void nodeOneOfUndoCommand(int index);
	void nodeTwoOfUndoCommand(int index);

	void nodeOneOfExitCommand(int index);
	void nodeTwoOfExitCommand(int index);

	void nodeOneOfClearCommand(int index);
	void nodeTwoOfClearCommand(int index);

	void nodeOneOfSearchCommand(int index);
	void nodeTwoOfSearchCommand(int index);

	void nodeOneOfAddCommand(int index);

	void nodeOneOfEditCommand(int index);
	void nodeTwoOfEditCommand(int index);

	void packDisplayCommand();
	void packChangeViewTypeCommand();
	void packChangeDirectoryCommand();
	void packDeleteCommand();
	void packUndoCommand();
	void packExitCommand();
	void packClearCommand();
	void packSearchCommand();
	void packAddCommand();
	void packEditCommand();
	void packInvalidCommand();
};