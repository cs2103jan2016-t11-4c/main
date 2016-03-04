#include "Command_ViewType.h"

Command_ViewType::Command_ViewType(Settings* settings, int newViewType)
:Command(NULL, NULL) {
	_settings = settings;
	_oldViewType = _settings->getViewType();
	_newViewType = newViewType;
}

void Command_ViewType::execute() {
	_settings->changeViewType(_newViewType);
	_UI->printNotificationViewTypeChange(_newViewType);
}

void Command_ViewType::undo(){
	_settings->changeViewType(_oldViewType);
	_UI->printNotificationViewTypeChange(_oldViewType);	
}