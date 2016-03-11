#include "Command_ViewType.h"

Command_ViewType::Command_ViewType(Settings* settings, int newViewType)
:Command(NULL) {
	_settings = settings;
	_oldViewType = _settings->getViewType();
	_newViewType = newViewType;
}

bool Command_ViewType::execute() {
	_settings->changeViewType(_newViewType);
	return true;
}

bool Command_ViewType::undo(){
	_settings->changeViewType(_oldViewType);
	return true;	
}

int Command_ViewType::getIndex() {
	return _newViewType;
}

//COMMAND_TYPE Command_ViewType::getCommandType() {
//	return VIEWTYPE;
//}