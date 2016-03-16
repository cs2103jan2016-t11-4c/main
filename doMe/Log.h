#include <string>
#include <fstream>
using namespace std;

class Log {
private:
	static Log* _instance;
	Log();
public:
	static Log* getInstance();
	void record(string entry);
};