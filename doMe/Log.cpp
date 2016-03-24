#include "Log.h"

Log* Log::_instance = 0;
const string Log::LOG_FILE_NAME = "doMeLog.txt";

Log::Log() {
	_storage = Storage::getInstance();
	_logText = _storage->retrieveData(LOG_FILE_NAME);
}

Log* Log::getInstance() {
	if (_instance == 0) {
		_instance = new Log;
	}
	return _instance;
}

void Log::record(string entry) {
	_logText.push_back(entry);

	_storage->saveData(_logText, LOG_FILE_NAME);
}

void Log::record(string entry, COMMAND_TYPE commandType) {
	string commandTypeString;

	switch(commandType) {
    case ADD:
		commandTypeString = "ADD";
        break;
    case DISPLAY:
		commandTypeString = "DISPLAY";
        break;
    case DEL:
		commandTypeString = "DEL";
        break;
    case EDIT:
		commandTypeString = "EDIT";
        break;
    case CLEAR:
		commandTypeString = "CLEAR";
        break;
    case UNDO:
		commandTypeString = "UNDO";
        break;
    case SORT:
		commandTypeString = "SORT";
        break;
    case SEARCH:
		commandTypeString = "SEARCH";
        break;
    case ENDSEARCH:
		commandTypeString = "ENDSEARCH";
        break;
    case VIEWTYPE:
		commandTypeString = "VIEWTYPE";
        break;
    case SAVEDIRECTORY:
		commandTypeString = "SAVEDIRECTORY";
        break;
    case EXIT:
		commandTypeString = "EXIT";
        break;
    case INVALID:
		commandTypeString = "INVALID";
        break;
    default:
        break;
	}

	_logText.push_back(entry + commandTypeString + " command");

	_storage->saveData(_logText, LOG_FILE_NAME);
}

void Log::record(Task* task) {
	string name = task->getName();
	string time1 = integerToString(task->getTime1());
	string time2 = integerToString(task->getTime2());
	string date1 = integerToString(task->getDate1());
	string date2 = integerToString(task->getDate2());
	string location = task->getLocation();

	_logText.push_back("Task with parameters: ( " + name + time1 + time2 + date1 + date2 + location + " ) added");

	_storage->saveData(_logText, LOG_FILE_NAME);
}

string Log::integerToString(int integer) {
	ostringstream word;
	word << integer;
	return word.str();
}