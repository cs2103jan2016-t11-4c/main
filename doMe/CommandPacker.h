//@@author A0122569B
//
//This is the CommandPacker. This class creates the appropriate command object based on the 
//lexed tokens passed to it. It is an singleton class and pointer to the object should be 
//retrieved using the CommandPacker::getInstance() method.
//The main API is Command* packCommand(InputTokens* tokens);
//description: makes a command object baed on the tokens passed to it and returns the address 
//to the command object.
//Pre-Condition: The tokens pointer should not be NULL
//Post-Condition: A Command object would be created. If required, a Task Object may also be created


#pragma once

#include "Command.h"
#include "Command_Add.h"
#include "Command_Clear.h"
#include "Command_Edit.h"
#include "Command_Exit.h"
#include "Command_Scroll.h"
#include "Command_Invalid.h"
#include "Command_SaveDirectory.h"
#include "Command_Search.h"
#include "Command_Undo.h"
#include "Command_ViewType.h"
#include "Command_Help.h"
#include "Command_Redo.h"
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
	bool _isDeleteDate;
	bool _isDeleteTime;
	bool _isDeleteLocation;
	int _doneStatus;

	void setEnvironment(InputTokens* tokens);
	void branchToNode(int index); //branches to the various command nodes for parsing

	//Below are the method nodes that check an aspect of every command. The part in the []brackets is the part being checked
	void nodeOneOfDisplayCommand(int index);			//display [1]

	void nodeOneOfChangeDirectoryCommand(int index);	//change [the] directory to some address
	void nodeTwoOfChangeDirectoryCommand(int index);	//change the [directory] to some address 
	void nodeThreeOfChangeDirectoryCommand(int index);	//change the directory [to] some address
	void nodeFourOfChangeDirectoryCommand(int index);	//change the directory to [some address]

	void nodeOneOfChangeViewTypeCommand(int index);		//change the [viewtype] to index
	void nodeTwoOfChangeViewTypeCommand(int index);		//change the viewtype [to] index
	void nodeThreeOfChangeViewTypeCommand(int index);	//change the viewtype to [index]
	void nodeFourOfChangeViewTypeCommand(int index);	//change the viewtype to index []

	void nodeOneOfDeleteCommand(int index);				//delete [1] location date time
	void nodeTwoOfDeleteCommand(int index);				//delete 1 [location] date time
	void nodeThreeOfDeleteCommand(int index);			//delete 1 location [date time]

	void nodeOneOfUndoCommand(int index);				//undo []

	void nodeOneOfRedoCommand(int index);				//redo []

	void nodeOneOfHelpCommand(int index);				//help []

	void nodeOneOfExitCommand(int index);				//exit []

	void nodeOneOfScrollCommand(int index);				//b []

	void nodeOneOfClearCommand(int index);				//clear [] 
	void nodeTwoOfClearCommand(int index);				//clear [all]
	void nodeThreeOfClearCommand(int index);			//clear all []
	void nodeFourOfClearCommand(int index);				//clear [1]-5
	void nodeFiveOfClearCommand(int index);				//clear 1[-]5
	void nodeSixOfClearCommand(int index);				//clear 1-[5]
	void nodeSevenOfClearCommand(int index);			//clear 1-5 [location date time]

	void nodeOneOfSearchCommand(int index);				//search [for] the meaning of life
	void nodeTwoOfSearchCommand(int index);				//search for [the meaning of life]
	void nodeThreeOfSearchCommand(int index);

	void nodeOneOfMarkCommand(int index);				//mark [1]-3 as not done
	void nodeTwoOfMarkCommand(int index);				//mark 1[-]3 as not done
	void nodeThreeOfMarkCommand(int index);				//mark 1-[3] as not done
	void nodeFourOfMarkCommand(int index);				//mark 1-3 as [not] done
	void nodeFiveOfMarkCommand(int index);				//mark 1-3 as not [done]
	void nodeSixOfMarkCommand(int index);				//mark [as] not done 1-3
	void nodeSevenOfMarkCommand(int index);				//mark as [not] done 1-3
	void nodeEightOfMarkCommand(int index);				//mark as not [done] 1-3
	void nodeNineOfMarkCommand(int index);				//mark as not done [1]-3
	void nodeTenOfMarkCommand(int index);				//mark as not done 1[-]3
	void nodeElevenOfMarkCommand(int index);			//mark as not done 1-[3]
	void nodeTwelveOfMarkCommand(int index);			//mark as not done 1-3 []

	void nodeOneOfAddCommand(int index);				//[add] submit everything 11 apr 2359
	void nodeTwoOfAddCommand(int index);				//add [submit everything 11 apr 2359]

	void nodeOneOfEditCommand(int index);				//edit [1] to just give up
	void nodeTwoOfEditCommand(int index);				//edit 1 [to] just give up
	void nodeThreeOfEditCommand(int index);				//edit 1 to [just give up]

	//uses global variables to pack the command object
	void packDisplayCommand();
	void packChangeViewTypeCommand();
	void packChangeDirectoryCommand();
	void packDeleteCommand();
	void packDeleteTaskParametersCommand();
	void packUndoCommand();
	void packRedoCommand();
	void packHelpCommand();
	void packExitCommand();
	void packScrollCommand();
	void packClearCommand();
	void packSearchCommand();
	void packMarkCommand();
	void packAddCommand();
	void packEditCommand();
	void packInvalidCommand();

	void extractTerm(int index);			//reads in tokens till the end and stores the read string in _description

	void extractDeleteParameter(int index);	//finds the parameter to delete from a task
	void packDeleteTask();					//packs up the parameters for task deletion

	void addToIndexes(int index);			//adds an integer to the global _indexes variable
	void addRangeToIndexes(int index);		//adds a range of integer to the global _indexes variable
};