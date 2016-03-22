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