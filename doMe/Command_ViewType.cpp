#include "Command_ViewType.h"

Command_ViewType::Command_ViewType(Settings* settings, int newViewType)
:Command(NULL) {
	_settings = settings;
	_oldViewType = _settings->getViewType();
	_newViewType = newViewType;
}

int Command_ViewType::execute() {
	_settings->changeViewType(_newViewType);
	return 1;
}

int Command_ViewType::undo(){
	_settings->changeViewType(_oldViewType);
	return 1;	
}

int Command_ViewType::getIndex() {
	return _newViewType;
}