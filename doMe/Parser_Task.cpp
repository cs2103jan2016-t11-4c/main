#include "Parser_Task.h"


Parser_Task::Parser_Task(CommandArguments* arguments) :
	_arguments(arguments)
{
}


Parser_Task::~Parser_Task(void)
{
}

CommandPackage parse() {
	return CommandPackage();
}
