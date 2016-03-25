//@@author A0125290M
#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Task.h"
#include "Command.h"
#include "Exception_InvalidCommand.h"
#include "Exception_ExceededParameterLimit.h"
#include "Exception_FileCannotOpen.h"
using namespace std;

#define	CURRENT_TIME getCurrentTime()
#define	CURRENT_DATE getCurrentDate()
#define CURRENT_DAY getCurrentDay()
#define LOG(file, message) Commons::log(file, message)

class Commons {
public:
	static void log(string file, string message);
	Commons();

	static const string LOG_FILE_NAME;
	static const string LOG_ENTRY;
	static const string TIME_DIVIDER;

	static string getCurrentTime();		//HH:MM:SS Format
	static int getCurrentDate();		//YYYYMMDD Format
	static int getCurrentDay();		//MON = 1, TUE = 2 etc.
	static string integerToString(int integer);
	static string trim(string file);
};