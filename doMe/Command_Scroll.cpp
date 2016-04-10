//@@author A0125290M
#include "Command_Scroll.h"	
Command_Scroll::Command_Scroll()
		:Command() {
}
CommandType Command_Scroll::getCommandType() {
	return SCROLL;
}
string Command_Scroll::getStringForm() {
	return "Scroll";
}