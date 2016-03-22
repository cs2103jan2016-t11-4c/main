//@@author A0125290M
#include <iostream>
#include <string>
#include <stack>
#include <assert.h>
#include "Parser.h"
#include "Memory.h"
#include "Command.h"
#include "Exception_InvalidCommand.h"
//#include "Command_Add.h"
//#include "Command_Clear.h"
//#include "Command_Delete.h"
//#include "Command_Edit.h"
//#include "Command_Exit.h"
//#include "Command_Invalid.h"
//#include "Command_SaveDirectory.h"
//#include "Command_Search.h"
//#include "Command_Undo.h"
//#include "Command_ViewType.h"
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