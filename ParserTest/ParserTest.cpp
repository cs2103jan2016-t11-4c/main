//@@author A0122569B

#include "stdafx.h"
#include "CppUnitTest.h"

#include "Exception_CorruptedFile.cpp"
#include "Exception_FirstTimeUser.cpp"
#include "Exception_FileCannotOpen.cpp"
#include "Exception_InvalidCommand.cpp"
#include "Exception_ExceededParameterLimit.cpp"
#include "Commons.cpp"
#include "Task.cpp"
#include "Memory.cpp"
#include "Settings.cpp"
#include "RAM.cpp"
#include "Storage.cpp"
#include "Command.cpp"
#include "Command_Add.cpp"
#include "Command_help.cpp"
#include "Command_Redo.cpp"
#include "Command_Clear.cpp"
#include "Command_Edit.cpp"
#include "Command_Exit.cpp"
#include "Command_Invalid.cpp"
#include "Command_Scroll.cpp"
#include "Command_SaveDirectory.cpp"
#include "Command_Search.cpp"
#include "Command_Undo.cpp"
#include "Command_ViewType.cpp"
#include "SynonymList.cpp"
#include "Dictionary.cpp"
#include "InputTokens.cpp"
#include "ChronoInterpreter.cpp"
#include "TaskPacker.cpp"
#include "CommandPacker.cpp"
#include "Parser_Interface.cpp"
#include "Parser.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ParserTest
{		
	TEST_CLASS(AddTest)
	{
	public:
		//these cases are to test different pathways when adding tasks
		TEST_METHOD(Parser_Add_Simple)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home");
			Command* expected = new Command_Add(new Task("go home"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Add_NaturalLanguage)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("add go home");
			Command* expected = new Command_Add(new Task("go home"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Add_1Date)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 1/2/2005");
			Command* expected = new Command_Add(new Task("go home",NO_DATE, 20050201));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Add_2Date)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 01/02/2005 03/02/2005");
			Command* expected = new Command_Add(new Task("go home", 20050201, 20050203));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Add_1Time)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 2359 hrs");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, NO_TIME, 2359));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Add_2Time)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 2358 hrs 2359hrs");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, 2358, 2359));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Add_Location)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home @istanah");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, NO_DATE, NO_TIME, NO_TIME, "istanah"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Add_MultiWordLocation)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home @the grand buddapest hotel");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, NO_DATE, NO_TIME, NO_TIME, "the grand buddapest hotel"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Add_All)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go on holiday 03/2/2016 800hrs @the grand buddapest hotel 04/02 1800hrs ");
			Command* expected = new Command_Add(new Task("go on holiday", 20160203, 20160204, 800, 1800, "the grand buddapest hotel"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Add_All_doneStatus)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go on holiday 03/2/2016 800hrs @the grand buddapest hotel 04/02 1800hrs done");
			Command* expected = new Command_Add(new Task("go on holiday", 20160203, 20160204, 800, 1800, "the grand buddapest hotel", 1));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}
	};

		TEST_CLASS(IgnoreTest)
	{
	public:
		//these cases are to test functionality of *command to ignore parsing
		TEST_METHOD(Parser_Ignore_Search)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("*search for house keys");
			Command* expected = new Command_Add(new Task("search for house keys"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Ignore_Digits)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("hit target of making a *1000 sales");
			Command* expected = new Command_Add(new Task("hit target of making a 1000 sales"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Ambiguity_4Digits)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("hit target of making a $1000 worth of sales");
			Command* expected = new Command_Add(new Task("hit target of making a $1000 worth of sales"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Ambiguity_4Digits_Back)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("hit target of making a 1000dollas worth of sales");
			Command* expected = new Command_Add(new Task("hit target of making a 1000dollas worth of sales"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Ambiguity_6Digits)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go friends house @blah blah blk blah S160405");
			Command* expected = new Command_Add(new Task("go friends house", -1, -1, -1, -1, "blah blah blk blah S160405"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}
	};

	TEST_CLASS(ChronoTest)//this class tests interpretation
	{
	public:
		//Following test cases based on equivalence partitioning.
		TEST_METHOD(Parser_ValidDate_LowerBorder)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 01012016");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, 20160101));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_ValidDate_HigherBorder)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 31122016");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, 20161231));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_InvalidDay_TooHigh)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 32032016");
			Command* expected = new Command_Add(new Task("go home 32032016"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_InvalidDay_TooLow)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 00012016");
			Command* expected = new Command_Add(new Task("go home 00012016"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_InvalidMonth_TooHigh)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 21132016");
			Command* expected = new Command_Add(new Task("go home 21132016"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_InvalidMonth_TooLow)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 21002016");
			Command* expected = new Command_Add(new Task("go home 21002016"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_ValidLeapYear)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 29/2/2016");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, 20160229));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_InvalidLeapYear)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 29022015");
			Command* expected = new Command_Add(new Task("go home 29022015"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_InvalidLeapYear_YearMultipleOf100)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 29022100");
			Command* expected = new Command_Add(new Task("go home 29022100"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_ValidLeapYear_YearMultipleOf400)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 29022400");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, 24000229));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_ValidTime_UpperBorder)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 2359");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, NO_TIME, 2359));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_ValidTime_LowerBorder)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home tday 0000");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, NO_TIME, 0));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_InvalidMinute_TooHigh)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home tday 0060");
			Command* expected = new Command_Add(new Task("go home 0060"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_InvalidHour_TooHigh)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 2400");
			Command* expected = new Command_Add(new Task("go home 2400hrs"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		//following test cases in chrono test are all based on pathways
		TEST_METHOD(Parser_TimeFormatA_4Digit)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home tday 0000hrs");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, NO_TIME, 0));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeFormatA_3Digit)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home tday 800hrs");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, NO_TIME, 800));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeFormatA_Ambiguity1)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 12th feb 1330");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, 20160212, NO_TIME, 1330));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeFormatA_Ambiguity2)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home feb 12 1330");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, 20160212, NO_TIME, 1330));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeFormatA_Ambiguity3)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home feb 12 17 1330");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, 20170212, NO_TIME, 1330));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeFormatB_1Digit)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home tday 1am");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, NO_TIME, 100));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeFormatB_2Digit)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home tday 11am");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, NO_TIME, 1100));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeFormatB_3Digit)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home tday 130am");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, NO_TIME, 130));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeFormatB_4Digit)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home tday 1130am");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, NO_TIME, 1130));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeFormatB_PMTest)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home tday 1130pm");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, NO_TIME, 2330));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeFormatB_12AM)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home tday 1230am");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, NO_TIME, 30));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeFormatB_12PM)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home tday 1230pm");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, NO_TIME, 1230));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}
		
		TEST_METHOD(Parser_TimeFormatB_NonsenseMeridiemTime)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 1330pm tday");
			Command* expected = new Command_Add(new Task("go home 1330pm", NO_DATE, DATE));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeRangeFormatA_Standard)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 8-1130pm tday");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, 2000, 2330));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeRangeFormatA_InversedMeridiem)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 8-230pm tday");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, 800, 1430));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeRangeFormatA_InversedMeridiem_NextDay)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 8-230am tday");
			Command* expected = new Command_Add(new Task("go home", DATE, ADD_TO_DATE(1, DATE), 2000, 230));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeRangeFormatA_XXTo12am)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 8-1230am tday");
			Command* expected = new Command_Add(new Task("go home", DATE, ADD_TO_DATE(1, DATE), 2000, 30));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeRangeFormatA_XXTo12pm)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 8-1230pm tday");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, 800, 1230));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeRangeFormatA_12ToXXam)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 12-1130am tday");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, 0, 1130));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeRangeFormatA_12ToXXpm)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 1215-1130pm tday");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, 1215, 2330));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeRangeFormatA_12To12am)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 12-1230am tday");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, 0, 30));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeRangeFormatA_12To12pm)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 1215-1230pm tday");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, 1215, 1230));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeRangeFormatA_12To12am_Reversed)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 1245-1230am ADD_TO_DATE(1, DATE)");
			Command* expected = new Command_Add(new Task("go home", DATE, ADD_TO_DATE(1, DATE), 1245, 30));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeRangeFormatA_12To12pm_Reversed)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 1245-1230pm tday");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, 45, 1230));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeRangeFormatA_24Hrs)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 800-1130hrs tday");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, 800, 1130));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeRangeFormatA_24Hrs_Reversed)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 1100-1030hrs tday");
			Command* expected = new Command_Add(new Task("go home", DATE, ADD_TO_DATE(1, DATE), 1100, 1030));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeRangeFormatA_24Hrs_1digit)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 8-1030hrs tday");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, 800, 1030));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateFormatA_Type1)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 2/3");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, 20160302));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateFormatA_Type2)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 21/3");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, 20160321));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateFormatA_Type3)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 1/11");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, 20161101));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateFormatA_Type4)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 22/11");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, 20161122));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateFormatA_Type5)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 22/11/18");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, 20181122));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateFormatA_Type6)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 22/11/2117");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, 21171122));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateFormatC_Type1)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home feb 3rd");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, 20160203));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateFormatC_Type2)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home feb 3");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, 20160203));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateFormatD_Type1)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 3 feb");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, 20160203));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateFormatD_Type2)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 2nd feb");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, 20160202));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateFormatD_Type3)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 4th feb 17");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, 20170204));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateFormatD_Type4)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 4feb17");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, 20170204));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateFormatD_Invalid)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 3th feb 17");
			Command* expected = new Command_Add(new Task("go home 3th", NO_DATE, 20160217));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateFormatE_Type1)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home today");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateFormatE_Type2)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home tmr");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, ADD_TO_DATE(1, DATE)));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateFormatE_Type3)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home yesterday");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, ADD_TO_DATE(-1, DATE)));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateFormatE_Type4)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home next sunday");
			int daysToAdd = 14 - WEEK_DAY;
			Command* expected = new Command_Add(new Task("go home", NO_DATE, ADD_TO_DATE(daysToAdd, DATE)));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateFormatE_Type5)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home sat");
			int daysToAdd = (13 - WEEK_DAY) % 7;
			if(daysToAdd == 0) {
				daysToAdd += 7;
			}
			Command* expected = new Command_Add(new Task("go home", NO_DATE, ADD_TO_DATE(daysToAdd, DATE)));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateFormatE_Type6)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home next week");
			int daysToAdd = 14 - WEEK_DAY;
			if(daysToAdd == 7) {
				daysToAdd += 7;
			}
			Command* expected = new Command_Add(new Task("go home", NO_DATE, ADD_TO_DATE(daysToAdd, DATE)));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateFormatE_Type7)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home this week");
			int daysToAdd = 7 - WEEK_DAY;
			if(daysToAdd == 0) {
				daysToAdd += 7;
			}
			Command* expected = new Command_Add(new Task("go home", NO_DATE, ADD_TO_DATE(daysToAdd, DATE)));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateFormatE_Type8)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home this sun");
			int daysToAdd = 7 - WEEK_DAY;
			if(daysToAdd == 0) {
				daysToAdd += 7;
			}
			Command* expected = new Command_Add(new Task("go home", NO_DATE, 20160410));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateFormatE_Invalid_Type1)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home week");
			Command* expected = new Command_Add(new Task("go home week"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateFormatE_Invalid_Type2)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home this today");
			Command* expected = new Command_Add(new Task("go home this", NO_DATE, DATE));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateRangeFormatA_Type1)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 3rd to 5th feb 17");
			Command* expected = new Command_Add(new Task("go home", 20170203, 20170205));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateRangeFormatA_Type2)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 5th to 3rd feb 17");
			Command* expected = new Command_Add(new Task("go home", 20170203, 20170205));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateRangeFormatA_Type3)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 5 to 3rd feb 17");
			Command* expected = new Command_Add(new Task("go home", 20170203, 20170205, 1000, 2000));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateRangeFormatA_Type4)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 8pm 5th to 1000 3rd feb 17");
			Command* expected = new Command_Add(new Task("go home", 20170203, 20170205, 1000, 2000));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateRangeFormatA_Type5)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 8pm 5 to 1000 3rd feb 17");
			Command* expected = new Command_Add(new Task("go home", 20170203, 20170205, 1000, 2000));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateRangeFormatB_Type1)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home feb 17th-19th");
			Command* expected = new Command_Add(new Task("go home", 20160217, 20160219));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateRangeFormatB_Type2)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home feb 19th-17th");
			Command* expected = new Command_Add(new Task("go home", 20160217, 20160219));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateRangeFormatB_Type3)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home feb 19th -17");
			Command* expected = new Command_Add(new Task("go home", 20160217, 20160219, 1900, 2000));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}
		
		TEST_METHOD(Parser_DateRangeFormatB_Type4)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home feb 19th 2000hrs-17th 7 pm");
			Command* expected = new Command_Add(new Task("go home", 20160217, 20160219, 1900, 2000));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateRangeFormatB_Type5)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home feb 19th 2000hrs-17th 7 pm");
			Command* expected = new Command_Add(new Task("go home", 20160217, 20160219, 1900, 2000));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}
	};

	TEST_CLASS(EditTest)
	{
	public:
		
		TEST_METHOD(Parser_Edit_Valid)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("edit 1 go home");
			vector<int>* intVector = new vector<int>;
			intVector->push_back(1);
			Command* expected = new Command_Edit(intVector, new Task("go home", -2, -2, -2, -2, " ", -1));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Edit_LastIndex)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("edit go home");
			vector<int>* intVector = new vector<int>;
			intVector->push_back(0);
			Command* expected = new Command_Edit(intVector, new Task("go home", -2, -2, -2, -2, " ", -1));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Edit_Valid_NaturalLanguage)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("edit 1 to go home");
			vector<int>* intVector = new vector<int>;
			intVector->push_back(1);
			Command* expected = new Command_Edit(intVector, new Task("go home", -2, -2, -2, -2, " ", -1));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Edit_LastIndex_NaturalLanguage)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("edit to go home");
			vector<int>* intVector = new vector<int>;
			intVector->push_back(0);
			Command* expected = new Command_Edit(intVector, new Task("go home", -2, -2, -2, -2, " ", -1));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Edit_Ambiguity)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("edit 1 apr");
			vector<int>* intVector = new vector<int>;
			intVector->push_back(0);
			Command* expected = new Command_Edit(intVector, new Task("", -2, 20160401, -2, -2, " ", -1));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}
	};

	TEST_CLASS(ClearTest)
	{
	public:
		
		TEST_METHOD(Parser_Clear_All)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("clr");
			Command* expected = new Command_Clear(new vector<int>);
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Clear_Invalid)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("clear your system of toxins");
			Command* expected = new Command_Add(new Task("clear your system of toxins"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Clear_All_NaturalLanguage)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("clr everytin");
			Command* expected = new Command_Clear(new vector<int>);
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Clear_All_NaturalLanguage_Alternate)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("del everytin");
			Command* expected = new Command_Clear(new vector<int>);
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Clear_Indexes)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("clr 1 2 3 4");
			vector<int>* intVector = new vector<int>;
			intVector->push_back(1);
			intVector->push_back(2);
			intVector->push_back(3);
			intVector->push_back(4);
			Command* expected = new Command_Clear(intVector);
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Clear_Indexes_Repeats)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("clr 1 2 3 4 2");
			vector<int>* intVector = new vector<int>;
			intVector->push_back(1);
			intVector->push_back(3);
			intVector->push_back(4);
			intVector->push_back(2);
			Command* expected = new Command_Clear(intVector);
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Clear_IndexRange)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("clr 1-4");
			vector<int>* intVector = new vector<int>;
			intVector->push_back(1);
			intVector->push_back(2);
			intVector->push_back(3);
			intVector->push_back(4);
			Command* expected = new Command_Clear(intVector);
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Clear_IndexRange_Repeats)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("clr 3 5 6 1 to 4");
			vector<int>* intVector = new vector<int>;
			intVector->push_back(5);
			intVector->push_back(6);
			intVector->push_back(1);
			intVector->push_back(2);
			intVector->push_back(3);
			intVector->push_back(4);
			Command* expected = new Command_Clear(intVector);
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Clear_AlternatePath)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("del 1 7 8 1 2");
			vector<int>* intVector = new vector<int>;
			intVector->push_back(7);
			intVector->push_back(8);
			intVector->push_back(1);
			intVector->push_back(2);
			Command* expected = new Command_Clear(intVector);
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Clear_MassParameter)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("del 1-5 location time");
			vector<int>* intVector = new vector<int>;
			intVector->push_back(7);
			intVector->push_back(8);
			intVector->push_back(1);
			intVector->push_back(2);
			Command* expected = new Command_Edit(intVector, new Task("", -2, -2, -1, -1, ""));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

	};

	TEST_CLASS(UndoTest)
	{
	public:
		
		TEST_METHOD(Parser_Undo_Valid)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("undo");
			Command* expected = new Command_Undo();
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Undo_Invalid)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("undo the calamities upon humanity");
			Command* expected = new Command_Add(new Task("undo the calamities upon humanity"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}
	};


	TEST_CLASS(RedoTest)
	{
	public:
		
		TEST_METHOD(Parser_Redo_Valid)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("redo");
			Command* expected = new Command_Redo();
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Redo_Invalid)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("redo doMe.txt");
			Command* expected = new Command_Add(new Task("redo doMe.txt"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}
	};

	TEST_CLASS(ScrollTest)
	{
	public:
		
		TEST_METHOD(Parser_Scroll_Valid)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("b");
			Command* expected = new Command_Scroll();
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Scroll_Invalid)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("scroll  through this document");
			Command* expected = new Command_Add(new Task("scroll  through this document"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}
	};

	TEST_CLASS(HelpTest)
	{
	public:
		
		TEST_METHOD(Parser_Help_Valid)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("HELP");
			Command* expected = new Command_Help();
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Help_Valid2)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("?");
			Command* expected = new Command_Help();
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Help_Invalid)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("? the hell you looking at?");
			Command* expected = new Command_Add(new Task("? the hell you looking at?"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}
	};

	TEST_CLASS(DeleteTest)
	{
	public:
		TEST_METHOD(Parser_Delete_Valid_LastIndex)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("d");
			vector<int>* intVector = new vector<int>;
			intVector->push_back(0);
			Command* expected = new Command_Clear(intVector);
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Delete_Valid)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("d 1");
			vector<int>* intVector = new vector<int>;
			intVector->push_back(1);
			Command* expected = new Command_Clear(intVector);
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Delete_Parameters)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("delete 1 -l -d -t");
			vector<int>* intVector = new vector<int>;
			intVector->push_back(1);
			Command* expected = new Command_Edit(intVector, new Task("", -1, -1, -1, -1, "", -1));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Delete_Parameters2)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("delete 1 -l -t");
			vector<int>* intVector = new vector<int>;
			intVector->push_back(1);
			Command* expected = new Command_Edit(intVector, new Task("", -2, -2, -1, -1, "", -1));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Delete_Parameters3)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("delete -t");
			vector<int>* intVector = new vector<int>;
			intVector->push_back(0);
			Command* expected = new Command_Edit(intVector, new Task("", -2, -2, -1, -1, " ", -1));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Delete_InValid)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("delete my browser history");
			Command* expected = new Command_Add(new Task("delete my browser history"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}


	};
	
	TEST_CLASS(ChangeDirectoryTest)
	{
	public:
		TEST_METHOD(Parser_ChangeDirectory_Valid_Type1)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("cd c://blargh/whatdoesafolderaddressevenlooklike/lol");
			Command* expected = new Command_SaveDirectory("c://blargh/whatdoesafolderaddressevenlooklike/lol");
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_ChangeDirectory_Valid_Type2)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("change directory c://blargh/whatdoesafolderaddressevenlooklike/lol");
			Command* expected = new Command_SaveDirectory("c://blargh/whatdoesafolderaddressevenlooklike/lol");
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_ChangeDirectory_InValid_Type1)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("change directory");
			Command* expected = new Command_Invalid();
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_ChangeDirectory_InValid_Type2)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("cd");
			Command* expected = new Command_Invalid();
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}
	};

	TEST_CLASS(ChangeViewTypeTest)
	{
	public:
		
		TEST_METHOD(Parser_ChangeViewType_Valid_Type1)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("cv 2");
			Command* expected = new Command_ViewType(2);
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_ChangeViewType_Valid_Type2)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("change viewtype 2");
			Command* expected = new Command_ViewType(2);
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_ChangeViewType_Valid_Type3)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("view2");
			Command* expected = new Command_ViewType(2);
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_ChangeViewType_Valid_NaturalLanguage)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("change the viewtype to 2");
			Command* expected = new Command_ViewType(2);
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_ChangeViewType_InValid_Type1)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("change view");
			Command* expected = new Command_Invalid();
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_ChangeViewType_InValid_Type2)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("cv");
			Command* expected = new Command_Invalid();
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}
	};

	TEST_CLASS(SearchTest)
	{
	public:
		
		TEST_METHOD(Parser_Search_Valid)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("search water");
			Command* expected = new Command_Search("water");
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Search_Valid_NaturalLanguage)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("search for water");
			Command* expected = new Command_Search("water");
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Search_Valid_MultiWord)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("search for water in the sahara desert");
			Command* expected = new Command_Search("water in the sahara desert");
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Search_InValid)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("s");
			Command* expected = new Command_Invalid();
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}
	};

	TEST_CLASS(MarkTest)
	{
	public:
		
		TEST_METHOD(Parser_Mark_LastIndex)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("done");
			vector<int>* intVector = new vector<int>;
			intVector->push_back(0);
			Command* expected = new Command_Edit(intVector, new Task("", -2, -2, -2, -2, " ", 1));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}
		
		TEST_METHOD(Parser_Mark_LastIndex_notDone)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("not done");
			vector<int>* intVector = new vector<int>;
			intVector->push_back(0);
			Command* expected = new Command_Edit(intVector, new Task("", -2, -2, -2, -2, " ", 0));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Mark)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("1 done");
			vector<int>* intVector = new vector<int>;
			intVector->push_back(1);
			Command* expected = new Command_Edit(intVector, new Task("", -2, -2, -2, -2, " ", 1));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Mark_Range)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("1-3 done");
			vector<int>* intVector = new vector<int>;
			intVector->push_back(1);
			intVector->push_back(2);
			intVector->push_back(3);
			Command* expected = new Command_Edit(intVector, new Task("", -2, -2, -2, -2, " ", 1));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Mark_Alternate)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("done 1");
			vector<int>* intVector = new vector<int>;
			intVector->push_back(1);
			Command* expected = new Command_Edit(intVector, new Task("", -2, -2, -2, -2, " ", 1));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Mark_Alternate_Range)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("done 1-3");
			vector<int>* intVector = new vector<int>;
			intVector->push_back(1);
			intVector->push_back(2);
			intVector->push_back(3);
			Command* expected = new Command_Edit(intVector, new Task("", -2, -2, -2, -2, " ", 1));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Mark_NaturalLanguage_LastIndex)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("mark as done");
			vector<int>* intVector = new vector<int>;
			intVector->push_back(0);
			Command* expected = new Command_Edit(intVector, new Task("", -2, -2, -2, -2, " ", 1));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Mark_NaturalLanguage_LastIndex_notDone)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("mark as not done");
			vector<int>* intVector = new vector<int>;
			intVector->push_back(0);
			Command* expected = new Command_Edit(intVector, new Task("", -2, -2, -2, -2, " ", 0));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Mark_NaturalLanguage)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("mark 1 as done");
			vector<int>* intVector = new vector<int>;
			intVector->push_back(1);
			Command* expected = new Command_Edit(0, new Task("", -2, -2, -2, -2, " ", 1));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Mark_NaturalLanguage_Range)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("mark 1-3 as done");
			vector<int>* intVector = new vector<int>;
			intVector->push_back(1);
			intVector->push_back(2);
			intVector->push_back(3);
			Command* expected = new Command_Edit(0, new Task("", -2, -2, -2, -2, " ", 1));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}
	};
}