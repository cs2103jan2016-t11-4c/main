#include <string>
#include <fstream>
#include <vector>
#include "Storage.h"
using namespace std;

class Log {
private:
	static Log* _instance;
	Storage* _storage;
	vector<string> _logText;

	static const string LOG_FILE_NAME;

	Log();
public:
	static Log* getInstance();
	void record(string entry);
};