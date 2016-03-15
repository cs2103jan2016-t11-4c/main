#include "Command_ViewType.h"

Command_ViewType::Command_ViewType(Memory* memory, int newViewType)
:Command(memory) {
	_oldViewType = _memory->getViewType();
	_newViewType = newViewType;
}

bool Command_ViewType::execute() {
	return _memory->changeViewType(_newViewType);
}

bool Command_ViewType::undo() {
	return _memory->changeViewType(_oldViewType);
}

int Command_ViewType::getViewType() {
	return _newViewType;
}

COMMAND_TYPE Command_ViewType::getCommandType() {
	return VIEWTYPE;
}