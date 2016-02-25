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

class Parser {
public:
	Parser(string commandLine = ""); // string to parse can be put in directly during construction
	~Parser(void);
	
	CommandPackage parse(); // run this method to parse a commandline and recieve the command package
	
	void setCommandLine(string commandLine); // command line to parse can be set using this method as well
	CommandPackage getCommandPackage(); // this method can be used to recieve the commandpackage after parsing

	//all attributes and methods below are for internal implementations, do not touch
private:
	string _commandLine;
	vector<string> _caseSensitiveCommandParameters;
	vector<string> _commandParameters;
	COMMAND_TYPE _commandType;
	CommandPackage _commandPackage;
		
	static const int COMMAND_POSITION = 0;
	static const int INDEX_POSITION = 1;
	static const int FIRST_PARAMETER_POSITION = 1;

public:
	void getParametersFromCommandLine();
	void guessCommandType();
	void findDetailsIfSimpleCommandType();
	void findDetailsIfNotSimpleCommandType();

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

	void packCommandIfConfirmedDisplayCommand();
	void packCommandIfConfirmedDeleteCommand();
	void packCommandIfConfirmedUndoCommand();
	void packCommandIfConfirmedSortCommand();
	void packCommandIfConfirmedSavedDirectoryCommand();
	void packCommandIfConfirmedExitCommand();

	vector<string> splitSentence(string commandLine);
	string makeAllCaps(string s);
	bool isInteger(string s);
};