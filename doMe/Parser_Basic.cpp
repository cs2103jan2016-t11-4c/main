#include "Parser_Basic.h"


Parser_Basic::Parser_Basic(CommandArguments* arguments) :
	_arguments(arguments)
{
}


Parser_Basic::~Parser_Basic(void)
{
}

CommandPackage Parser_Basic::parse() {
	startParseTree();

	return _commandPackage;
}

void Parser_Basic::startParseTree() {
	/*
	if(isDisplay(_arguments->getArgument(START_PARAMETER))
	
	if(isAdd(_commandParameters[COMMAND_POSITION])) {
		_commandType = ADD;
	} else if(isDisplay(_commandParameters[COMMAND_POSITION])) {
		_commandType = DISPLAY;
	} else if(isDelete(_commandParameters[COMMAND_POSITION])) {
		_commandType = DEL;
	} else if(isEdit(_commandParameters[COMMAND_POSITION])) {
		_commandType = EDIT;
	} else if(isClear(_commandParameters[COMMAND_POSITION])) {
		_commandType = CLEAR;
	} else if(isUndo(_commandParameters[COMMAND_POSITION])) {
		_commandType = UNDO;
	} else if(isSort(_commandParameters[COMMAND_POSITION])) {
		_commandType = SORT;
	} else if(isSearch(_commandParameters[COMMAND_POSITION])) {
		_commandType = SEARCH;
	} else if(isViewType(_commandParameters[COMMAND_POSITION])) {
		_commandType = VIEWTYPE;
	} else if(isSaveDirectory(_commandParameters[COMMAND_POSITION])) {
		_commandType = SAVEDIRECTORY;
	} else if(isExit(_commandParameters[COMMAND_POSITION])) {
		_commandType = EXIT;
	} else {
		_commandType = ADD;
	}
}

*/

}
