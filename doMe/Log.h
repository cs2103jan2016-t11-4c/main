#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "Storage.h"
#include "Command.h"
using namespace std;

class Log {
private:
	static Log* _instance;
	Storage* _storage;
	vector<string> _logText;

	static const string LOG_FILE_NAME;

	string integerToString(int integer);
	Log();
public:
	static Log* getInstance();
	void record(string entry);
	void record(string entry, COMMAND_TYPE commandType);
	void record(Task* task);
};