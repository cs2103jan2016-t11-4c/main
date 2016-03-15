/*#include "CommandPackage.h"

CommandPackage::CommandPackage(COMMAND_TYPE commandType, Task task, int index, string description) :
	_commandType(commandType),
	_task(task),
	_index(index),
	_description(description)
{
}

CommandPackage::~CommandPackage(void) {
}

COMMAND_TYPE CommandPackage::getCommandType() {
	return _commandType;
}

string CommandPackage::getCommandTypeString() {
	switch(_commandType) {
	case ADD:
		return "add";
		break;
	
	case DISPLAY:
		return "display";
		break;
	
	case DEL:
		return "del";
		break;
	
	case EDIT:
		return "edit";
		break;

	case CLEAR:
		return "clear";
		break;

	case UNDO:
		return "undo";
		break;
	
	case SORT:
		return "sort";
		break;

	case SEARCH:
		return "search";
		break;

	case ENDSEARCH:
		return "endsearch";

	case VIEWTYPE:
		return "viewtype";

	case SAVEDIRECTORY:
		return "savedirectory";
		break;
	
	case EXIT:
		return "exit";
		break;

	case INVALID:
		return "invalid";
		break;

	default:
		return "error in getcommandtypestring";
		break;
	}
	return "error in getcommandtypestring";
}

Task* CommandPackage::getTask() {
	return &_task;
}

int CommandPackage::getIndex() {
	return _index;
}

string CommandPackage::getDescription() {
	return _description;
}

void CommandPackage::setCommandType(COMMAND_TYPE commandType) {
	_commandType = commandType;
	return;
}

void CommandPackage::setTask(Task task) {
	_task = task;
	return;
}

void CommandPackage::setIndex(int index) {
	_index = index;
	return;
}

void CommandPackage::setDescription(string description) {
	_description = description;
	return;
}