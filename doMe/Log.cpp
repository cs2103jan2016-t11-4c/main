#include "Log.h"

Log* Log::_instance = 0;

Log::Log() {
}

Log* Log::getInstance() {
	if (_instance == 0) {
		_instance = new Log;
	}
	return _instance;
}

void Log::record(string entry) {
	ofstream writeFile("doMeLog.txt");

	writeFile << entry << endl;

	writeFile.close();
}