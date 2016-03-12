#include "Command.h"
using namespace std;

class Command_Edit : public Command {
private:
	Task* _task;
	int _index;
	string _newName;
	int _newDate1;
	int _newDate2;
	int _newTime1;
	int _newTime2;
	string _newLocation;

	string _oldName;
	int _oldDate1;
	int _oldDate2;
	int _oldTime1;
	int _oldTime2;
	string _oldLocation;

	bool outOfRange();
public:
	Command_Edit(Memory* memory, int index, Task* task);
	bool execute();
	bool undo();
	Task* getTask();
	COMMAND_TYPE getCommandType();
};

#include "Command_Edit.h"

Command_Edit::Command_Edit(Memory* memory, int index, Task* task)
:Command(memory) {
	_index = index;
	_newName = task->getName();
	_newDate1 = task->getDate1();
	_newDate2 = task->getDate2();
	_newTime1 = task->getTime1();
	_newTime2 = task->getTime2();
	_newLocation = task->getLocation();
}

bool Command_Edit::execute() {
	if(outOfRange()) {
		return false;
	}

	_task = _memory->getTask(_index);

	if(!_newName.empty()) {
		_oldName = _task->getName();
		_task->setName(_newName);
	}
	if(_newDate1 != -1) {
		_oldDate1 = _task->getDate1();
		_task->setDate1(_newDate1);
	}
	if(_newDate2 != -1) {
		_oldDate2 = _task->getDate2();
		_task->setDate2(_newDate2);
	}
	if(_newTime1 != -1) {
		_oldTime1 = _task->getTime1();
		_task->setTime1(_newTime1);
	}
	if(_newTime2 != -1) {
		_oldTime2 = _task->getTime2();
		_task->setTime2(_newTime2);
	}
	if(!_newLocation.empty()) {
		_oldLocation = _task->getLocation();
		_task->setLocation(_newLocation);
	}
	_ram->sort();
	return true;
}

bool Command_Edit::undo() {
	_task->setName(_oldName);
	_task->setTime1(_oldTime1);
	_task->setTime2(_oldTime2);
	_task->setDate1(_oldDate1);
	_task->setDate2(_oldDate2);
	_task->setLocation(_oldLocation);
	_ram->sort();
	return true;
}

Task* Command_Edit::getTask() {
	return _task;
}

COMMAND_TYPE Command_Edit::getCommandType() {
	return EDIT;
}

bool Command_Edit::outOfRange() {
	if(_index > _memory->ramGetSize() || _index < 0) {
		return true;
	}
	return false;
}