//@@author A0125290M
#include "Command_ViewType.h"

Command_ViewType::Command_ViewType(int newViewType)
	:Command() {
		_oldViewType = _memory->getViewType();
		_newViewType = newViewType;
}

bool Command_ViewType::execute() {
	if(_memory->changeViewType(_newViewType)) {
		return true;
	}
	Exception_InvalidCommand e(this);
	throw e;
}

bool Command_ViewType::undo() {
	return _memory->changeViewType(_oldViewType);
}

int Command_ViewType::getViewType() {
	return _newViewType;
}

CommandType Command_ViewType::getCommandType() {
	return VIEWTYPE;
}

string Command_ViewType::getStringForm() {
	string s = "ViewType index: " + to_string(_newViewType);
	return s;
}