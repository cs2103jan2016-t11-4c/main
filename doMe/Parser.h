#pragma once
//This is the parser. It parses stuff. You give it a string of nonsense and it returns a totally structured and 
//comprehendable commandpackage
//How to use the parser:
//
//Step 1: Create a parser and pass it a string.
//This can be done during construction or setting it manually
//Example:
//Parser Jimmy("how do i use this?");
//or
//Parser Jimmy;
//Jimmy.setCommandLine("how do i use this?");
//
//Step 2: Run parse method and recieve your command package
//Example:
//commandPackage = Jimmy.parse();
//
//Additional Feature: If you lost the command package, you can still get the package using the getCommandPackage method
//Example:
//commandPackage = Jimmy.getCommandPackage();
//WARNING: Do not try to use getCommandPackage method before running the parse method.
//Feature if got time: Do not have to create a new Jimmy everytime you  need to parse
//
//@author: Mohammed Zawadul Farhan

#include "CommandPackage.h"
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>
#include <ctime>

class Parser {
public:
	Parser(string commandLine = ""); // string to parse can be put in directly during construction
	~Parser(void);
	
	CommandPackage* parse(); // run this method to parse a commandline and recieve the command package
	
	void setCommandLine(string commandLine); // command line to parse can be set using this method as well
	CommandPackage* getCommandPackage(); // this method can be used to recieve the commandpackage after parsing

	//all attributes and methods below are for internal implementations, do not touch
private:
	string _commandLine;
	vector<string> _caseSensitiveCommandParameters;
	vector<string> _commandParameters;
	COMMAND_TYPE _commandType;
	CommandPackage _commandPackage;
	vector<int> _times;
	int _time1;
	int _time2;
	vector<int> _dates;
	int _date2;
	int _date1;
	vector<string> _location;
	vector<string> _description;
	int _index;

	static const int COMMAND_POSITION = 0;
	static const int INDEX_POSITION = 1;
	static const int FIRST_PARAMETER_POSITION = 1;

public:

	//Highest level of abstraction methods
	void getParametersFromCommandLine();
	void guessCommandType();
	void findDetailsIfSimpleCommandType();
	void findDetailsIfNotSimpleCommandType();
	void parseAsAddCommandIfStillNotParsed();

	//booleans methods to identify markers of each command
	bool isAdd(string s);
	bool isDisplay(string s);
	bool isDelete(string s);
	bool isEdit(string s);
	bool isClear(string s);
	bool isUndo(string s);
	bool isSort(string s);
	bool isSearch(string s);
	bool isViewType(string s);
	bool isSaveDirectory(string s);
	bool isDirectory(string s);
	bool isExit(string s);

	//these methods do further checks on the parameters to see if it fits requirements of the commandtype
	//packs the commandpackage object if it complies and changes the commandtype if it does not
	void packCommandIfConfirmedDisplayCommand();
	void packCommandIfConfirmedDeleteCommand();
	void packCommandIfConfirmedUndoCommand();
	void packCommandIfConfirmedSortCommand();
	void packCommandIfConfirmedSavedDirectoryCommand();
	void packCommandIfConfirmedExitCommand();

	//methods below for similar function as those above. 
	//these methods, however deal with commands that are less specific in their format
	void packCommandIfConfirmedEditCommand();
	void packEditCommand();
	void packCommandIfConfirmedClearCommand();
	void packCommandIfConfirmedSearchCommand();
	void packCommandIfConfirmedViewTypeCommand();
	void packAddCommand();
	void removeAddCommand();
	void removeEditCommand();
	
	//these find the respective parameters from the parameters
	void getDateAndTimeParameters();
	void getLocationParameter();
	void getDescriptionParameter();

	bool extractIfIsDate(string s);
	bool tryExtractDateFormat1(string s);// ddmmyyyy
	bool tryExtractDateFormat2(string s);// ddmmyy
	bool tryExtractDateFormat3(string s);// dd/mm or d/mm or dd/mm or d/m
	bool tryExtractDateFormat4(string s);// dd/mm/yy or d/mm/yy or dd/mm/yy or d/m/yy (yy can be replace with yyyy)

	bool extractIfIsTime(string s);
	bool tryExtractTimeFormat1(string s);// hhmm (may have hrs at the end)

	//these methods identify starting and ending times from the amount of identified 
	bool finalizeDates();
	bool finalizeTimes();

	//methods to manipulate strings
	vector<string> splitSentence(string sentence);
	string combineWords(vector<string> stringVector);
	string makeAllCaps(string s);
	//removes a letter from a string. If no int value provided, removes the first letter by default.
	string removeLetter(string s, int n = 0);
	
	//boolean methods that recognize 
	bool isInteger(string s);
	bool isTime(string s);
	bool isDate(string s);
	bool isLocationMarker(string s);
	bool isValidDate(int date);
	bool isLeap(int year);

	int getCurrentDate();
};