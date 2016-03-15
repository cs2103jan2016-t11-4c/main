#pragma once
#include "CommandPackage.h"
#include "CommandTokens.h"
#include "Parser_Tasks.h"
#include "Task.h"
#include <string>
#include <assert.h>

#define LAST_INDEX -1

using namespace std;

class Parser_Algorithms
{
public:
	Parser_Algorithms(CommandTokens* tokens);
	~Parser_Algorithms(void);

private:
	CommandTokens* _tokens;
	CommandPackage _commandPackage;
	int _index;
	string _description;
	Task _task;

public:
	CommandPackage parse();
	void branchToNodes(int index);

	void nodeOneOfDisplayCommand(int index);
	void nodeTwoOfDisplayCommand(int index);
	void packDisplayCommand();

	void nodeOneOfChangeViewTypeCommand(int index);
	void nodeTwoOfChangeViewTypeCommand(int index);
	void nodeThreeOfChangeViewTypeCommand(int index);
	void packChangeViewTypeCommand();
	
	void nodeOneOfChangeDirectoryCommand(int index);
	void nodeTwoOfChangeDirectoryCommand(int index);
	void nodeThreeOfChangeDirectoryCommand(int index);
	void packChangeDirectoryCommand();

	void nodeOneOfDeleteCommand(int index);
	void nodeTwoOfDeleteCommand(int index);	
	void packDeleteCommand();

	void nodeOneOfUndoCommand(int index);
	void nodeTwoOfUndoCommand(int index);
	void packUndoCommand();

	void nodeOneOfExitCommand(int index);
	void nodeTwoOfExitCommand(int index);
	void packExitCommand();

	void nodeOneOfClearCommand(int index);
	void nodeTwoOfClearCommand(int index);
	void packClearCommand();

	void nodeOneOfSearchCommand(int index);
	void nodeTwoOfSearchCommand(int index);
	void packSearchCommand();

	void nodeOneOfAddCommand(int index);
	void packAddCommand();

	void nodeOneOfEditCommand(int index);
	void nodeTwoOfEditCommand(int index);
	void packEditCommand();

	void packInvalidCommand();
};