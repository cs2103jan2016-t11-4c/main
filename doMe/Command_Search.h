//@@author A0125290M
#pragma once
#include "Command.h"
using namespace std;

class Command_Search : public Command {
private:
	string _searchTerm;
public:
	Command_Search(string searchTerm);
	bool execute();
	bool undo();
	string getSearchTerm();
	CommandType getCommandType();
	string getStringForm();
};