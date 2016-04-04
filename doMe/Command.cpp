//@@author A0125290M
#include "Command.h"

Command::Command() {
	_memory = Memory::getInstance();
}

string Command::getCommandTypeStr() {
	switch(getCommandType()) {
	case ADD:
		return "ADD";
		break;
	case DISPLAY:
		return "DISPLAY";
		break;			
	case DEL:
		return "DEL";	
		break;
	case EDIT:
		return "EDIT";
		break;
	case CLEAR:
		return "CLEAR";
		break;
	case UNDO:
		return "UNDO";
		break;
	case REDO:
		return "REDO";
		break;
	case SORT:
		return "SORT";
		break;
	case SEARCH:
		return "SEARCH";
		break;
	case ENDSEARCH:
		return "ENDSEARCH";
		break;
	case VIEWTYPE:
		return "VIEWTYPE";
		break;
	case SAVEDIRECTORY:
		return "SAVEDIRECTORY";
		break;
	case EXIT:
		return "EXIT";
		break;
	case HELP:
		return "HELP";
		break;
	case INVALID:
		return "INVALID";
		break;
	}
	return "ERROR";
}