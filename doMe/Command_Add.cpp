//@@author A0125290M
#include "Command_Add.h"

Command_Add::Command_Add(Task* task)
:Command(){
	_task = task;
}

bool Command_Add::execute() {

	if(_task == NULL) {
		return false;
	}

	_memory->ramAdd(_task);

	return true;
}

bool Command_Add::undo() {
	_memory->ramDel(_task);
	return true;
}

Task* Command_Add::getTask() {
	return _task;
}

COMMAND_TYPE Command_Add::getCommandType() {
	return ADD;
}

string Command_Add::getStringForm() {
	string s = "Add task- ";
	s += "name: " + _task->getName();
	s += ", location: " + _task->getLocation();
	s += ", date1: " + to_string(_task->getDate1());
	s += ", date2: " + to_string(_task->getDate2());
	s += ", time1: " + to_string(_task->getTime1());
	s += ", time1: " + to_string(_task->getTime2());
	return s;
}