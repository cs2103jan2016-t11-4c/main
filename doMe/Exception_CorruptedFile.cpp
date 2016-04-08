//@@author A0125290M
#include "Exception_CorruptedFile.h"

const string Exception_CorruptedFile::ERROR_MESSAGE = "Corrupted doMe.txt found, new doMe.txt created.";

Exception_CorruptedFile::Exception_CorruptedFile() {
}

string Exception_CorruptedFile::getString() {
	return ERROR_MESSAGE;
}