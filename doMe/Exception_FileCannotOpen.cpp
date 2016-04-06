//@@author Joan

#include "Exception_FileCannotOpen.h"

Exception_FileCannotOpen::Exception_FileCannotOpen(string errorMsg)
{
	_errorMsg = errorMsg;
}


Exception_FileCannotOpen::~Exception_FileCannotOpen()
{
}

string Exception_FileCannotOpen::getString()
{
	return _errorMsg;
}
