#ifndef TESTMODE 

#else
#pragma once
/*
#include "Chrono.h"
#include "ViewType.h"
#include "ViewType1.h"
#include "ViewType2.h"
#include "Task.h"
#include "Command.h"
#include "Command_Add.h"
#include "Command_Delete.h"
#include "Command_Edit.h"
#include "Command_Clear.h"
#include "Command_ViewType.h"
#include "Command_SaveDirectory.h"
#include "Parser_Interface.h"
#include "Storage.h"
#include "Settings.h"
#include "UserInterface.h"
#include "InputTokens.h"
#include "Dictionary.h"
#include "SynonymList.h"
#include "ChronoInterpreter.h"
#include "CommandPacker.h"
#include "TaskPacker.h"
#include "Parser.h"
*/

#include "Task.cpp"
#include "Chrono.cpp"

//#include "Logic.cpp"
#include "Command.cpp"
#include "Command_Add.cpp"
#include "Command_Delete.cpp"
#include "Command_Edit.cpp"
#include "Command_Clear.cpp"
#include "Command_ViewType.cpp"
#include "Command_SaveDirectory.cpp"
#include "Command_Exit.cpp"
#include "Command_Invalid.cpp"
#include "Command_Search.cpp"
#include "Command_Undo.cpp"

#include "Storage.cpp"
#include "Settings.cpp"

#include "Memory.cpp"
#include "Log.cpp"
#include "RAM.cpp"

//#include "UserInterface.cpp"
#include "ViewType.cpp"
#include "ViewType1.cpp"
#include "ViewType2.cpp"
#include "Exception_InvalidCommand.cpp"
#include "Exception_Undo.cpp"


#include "Parser_Interface.cpp"
//#include "Parser.cpp"
//#include "CommandPacker.cpp"
#include "TaskPacker.cpp"

#include "ChronoInterpreter.cpp"
#include "InputTokens.cpp"
#include "Dictionary.cpp"
#include "SynonymList.cpp"

#endif


