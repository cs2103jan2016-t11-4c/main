//This is the Parser Class. It parses stuff. You give it a command in string form and it creates a
//totally structured and understandable Command object and returns back its address
//
//How to use the parser:
//
//Step 1: Get the address of the singleton Parser Object with the Parser::getInstance() method
//
//Description: Returns a pointer to the singleton object
//Pre-Condition: None
//Post-Condition: If an object of the class has not been initialized, the Parser object would be constructed
//
//Example:
//Parser* Jimmy = Parser::getInstance();
//
//Step 2: Run Command* parse(string) method with the string to parse as the parameter and recieve your command package
//
//Description: Creates a Command object based on the input string passed to it and returns the
//command object's address
//Pre-Condition: The string passed cannot be empty
//Post-Condition: A Command object will be created on the heap and the Parser Class will
//not be responsible for it's deletion
//
//Example:
//Command* command  = Jimmy->parse("How do I use this thing!?");
//
//@@author A0122569B

#pragma once

#include "Parser_Interface.h"
#include "CommandPacker.h"
#include "Command.h"
#include "InputTokens.h"
#include <string>
#include <assert.h>

using namespace std;

class Parser : public Parser_Interface
{
public:	
	~Parser(void);
	static Parser* getInstance();
	Command* parse(string userInput);

private:
	Parser(void);
	static Parser* _theOne;
	CommandPacker* _commandPacker;
};