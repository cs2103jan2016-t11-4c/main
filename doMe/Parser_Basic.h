#pragma once
#include "Parser.h"

class Parser_Basic
{
public:
	Parser_Basic(CommandArguments* arguments);
	~Parser_Basic(void);

private:
	CommandArguments* _arguments;
	CommandPackage _commandPackage;

public:
	CommandPackage parse();
	void startParseTree();

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
	bool isAt(string s);
};

