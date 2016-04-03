//This is the CommandPacker. This class creates the appropriate command object based on the 
//lexed tokens passed to it. It is an singleton class and pointer to the object should be 
//retrieved using the CommandPacker::getInstance() method.
//The main API is Command* packCommand(InputTokens* tokens);
//description: makes a command object baed on the tokens passed to it and returns the address 
//to the command object.
//Pre-Condition: The tokens pointer should not be NULL
//Post-Condition: A Command object would be created. If required, a Task Object may also be created
//
//@@author A0122569B

#pragma once

#include "Command.h"
#include "Command_Add.h"
#include "Command_Clear.h"
#include "Command_Delete.h"
#include "Command_Edit.h"
#include "Command_Exit.h"
#include "Command_Invalid.h"
#include "Command_SaveDirectory.h"
#include "Command_Search.h"
#include "Command_Undo.h"
#include "Command_ViewType.h"
#include "InputTokens.h"
#include "TaskPacker.h"
#include "Task.h"
#include "Exception_ExceededParameterLimit.h"
#include <string>
#include <assert.h>
#include <vector>

#define LAST_INDEX 0
#define NO_STRING ""

using namespace std;

class CommandPacker
{
public:
	~CommandPacker(void);
	static CommandPacker* getInstance();
	Command* packCommand(InputTokens* tokens);

private:
	CommandPacker(void);
	static CommandPacker* _theOne;
	
	TaskPacker* _taskPacker;
	InputTokens* _tokens;

	string _description;
	int _singleIndex;
	vector<int>* _indexes;
	Task* _task;
	Command* _command;

	void setEnvironment(InputTokens* tokens);
	void branchToNode(int index);

	void nodeOneOfDisplayCommand(int index);
	void nodeTwoOfDisplayCommand(int index);

	void nodeOneOfChangeDirectoryCommand(int index);
	void nodeTwoOfChangeDirectoryCommand(int index);
	void nodeThreeOfChangeDirectoryCommand(int index);
	void nodeFourOfChangeDirectoryCommand(int index);
	void nodeFiveOfChangeDirectoryCommand(int index);

	void nodeOneOfChangeViewTypeCommand(int index);
	void nodeTwoOfChangeViewTypeCommand(int index);
	void nodeThreeOfChangeViewTypeCommand(int index);
	void nodeFourOfChangeViewTypeCommand(int index);

	void nodeOneOfDeleteCommand(int index);
	void nodeTwoOfDeleteCommand(int index);	

	void nodeOneOfUndoCommand(int index);

	void nodeOneOfExitCommand(int index);

	void nodeOneOfClearCommand(int index);
	void nodeTwoOfClearCommand(int index);
	void nodeThreeOfClearCommand(int index);
	void nodeFourOfClearCommand(int index);
	void nodeFiveOfClearCommand(int index);
	void nodeSixOfClearCommand(int index);

	void nodeOneOfSearchCommand(int index);
	void nodeTwoOfSearchCommand(int index);
	void nodeThreeOfSearchCommand(int index);

	void nodeOneOfAddCommand(int index);

	void nodeOneOfEditCommand(int index);
	void nodeTwoOfEditCommand(int index);
	void nodeThreeOfEditCommand(int index);

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

	void addToIndexes(int index);
	void addRangeToIndexes(int index);

	void postProcessTask();
};