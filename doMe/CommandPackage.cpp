#include "CommandPackage.h"

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