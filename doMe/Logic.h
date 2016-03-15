#include <iostream>
#include <string>
#include <stack>
#include <assert.h>
#include <conio.h>
#include "Memory.h"
#include "Parser.h"
//#include "Commons.h"
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
using namespace std;

class Logic { 
private:
	Memory* _memory;
	stack<Command*>* _commandHistoryList;

	Command* undo();
public:
	Logic(Memory* memory);
	Command* executeCommand(string commandText, int& commandOutcome);
};