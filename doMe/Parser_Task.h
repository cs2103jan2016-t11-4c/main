#pragma once
#include "Parser.h"
class Parser_Task
{
public:
	Parser_Task(CommandArguments* arguments);
	~Parser_Task(void);

private:
	CommandArguments* _arguments;

public:
	CommandPackage parse();
};

