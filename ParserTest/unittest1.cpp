#include "stdafx.h"
#include "CppUnitTest.h"

#include "Exception_FileCannotOpen.cpp"
#include "Task.cpp"
#include "Memory.h"
#include "Memory.cpp"
#include "Settings.h"
#include "Settings.cpp"
#include "RAM.h"
#include "RAM.cpp"
#include "Storage.h"
#include "Storage.cpp"
#include "Command.cpp"
#include "Command_Add.cpp"
#include "Command_Clear.cpp"
#include "Command_Delete.cpp"
#include "Command_Edit.cpp"
#include "Command_Exit.cpp"
#include "Command_Invalid.cpp"
#include "Command_SaveDirectory.cpp"
#include "Command_Search.cpp"
#include "Command_Undo.cpp"
#include "Command_ViewType.cpp"
#include "Exception_ExceededParameterLimit.h"
#include "Exception_ExceededParameterLimit.cpp"
#include "Commons.h"
#include "Commons.cpp"
#include "SynonymList.h"
#include "SynonymList.cpp"
#include "Dictionary.h"
#include "Dictionary.cpp"
#include "InputTokens.h"
#include "InputTokens.cpp"
#include "ChronoInterpreter.h"
#include "ChronoInterpreter.cpp"
#include "TaskPacker.h"
#include "TaskPacker.cpp"
#include "CommandPacker.h"
#include "CommandPacker.cpp"
#include "Parser_Interface.h"
#include "Parser_Interface.cpp"
#include "Parser.h"
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
			Command* actual = sut->parse("go home 2005 hrs");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, NO_DATE, NO_TIME, 2005));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Add_2Time)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 2005 hrs 2100hrs");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, NO_DATE, 2005, 2100));
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
	};

	TEST_CLASS(ChronoTest)
	{
	public:
		//Following test cases based on equivalence partitioning
		TEST_METHOD(Parser_ValidDate_LowerBorder)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 01/01/2016");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, 20160101));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_ValidDate_HigherBorder)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 31/12/2016");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, 20161231));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_InvalidDay_TooHigh)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 32/03/2016");
			Command* expected = new Command_Add(new Task("go home 32/03/2016"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_InvalidDay_TooLow)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 00/01/2016");
			Command* expected = new Command_Add(new Task("go home 00/01/2016"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_InvalidMonth_TooHigh)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 21/13/2016");
			Command* expected = new Command_Add(new Task("go home 21/13/2016"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_InvalidMonth_TooLow)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 21/0/2016");
			Command* expected = new Command_Add(new Task("go home 21/0/2016"));
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
			Command* actual = sut->parse("go home 29/02/2015");
			Command* expected = new Command_Add(new Task("go home 29/02/2015"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_InvalidLeapYear_YearMultipleOf100)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 29/02/2100");
			Command* expected = new Command_Add(new Task("go home 29/02/2100"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_ValidLeapYear_YearMultipleOf400)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 29/02/2400");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, 24000229));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_ValidTime_UpperBorder)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 2359hrs");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, NO_DATE, NO_TIME, 2359));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_ValidTime_LowerBorder)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 0000hrs");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, NO_DATE, NO_TIME, 0));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_InvalidMinute_TooHigh)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 0060hrs");
			Command* expected = new Command_Add(new Task("go home 0060hrs"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_InvalidHour_TooHigh)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 2400hrs");
			Command* expected = new Command_Add(new Task("go home 2400hrs"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		//following test cases are based on pathways
		
		TEST_METHOD(Parser_TimeFormatA_Type1)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 0000hrs");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, NO_DATE, NO_TIME, 0));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeFormatB_1Digit)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 1am");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, NO_DATE, NO_TIME, 100));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeFormatB_2Digit)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 11am");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, NO_DATE, NO_TIME, 1100));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeFormatB_3Digit)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 130am");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, NO_DATE, NO_TIME, 130));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeFormatB_4Digit)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 1130am");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, NO_DATE, NO_TIME, 1130));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeFormatB_PMTest)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 1130pm");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, NO_DATE, NO_TIME, 2330));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeFormatB_12AM)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 1230am");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, NO_DATE, NO_TIME, 30));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeFormatB_12PM)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 1230pm");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, NO_DATE, NO_TIME, 1230));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}
		
		TEST_METHOD(Parser_TimeFormatB_NonsenseMeridiemTime)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 1330pm");
			Command* expected = new Command_Add(new Task("go home 1330pm"));
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


	};

	TEST_CLASS(EditTest)
	{
	public:
		
		TEST_METHOD(Parser_Edit_Valid)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("edit 1 go home");
			Command* expected = new Command_Edit(1, new Task("go home"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Edit_LastIndex)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("edit go home");
			Command* expected = new Command_Edit(0, new Task("go home"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

	};

	TEST_CLASS(ClearTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: Your test code here
		}

	};

	TEST_CLASS(UndoTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: Your test code here
		}

	};

	TEST_CLASS(DeleteTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{

		}

	};

	TEST_CLASS(ChangeDirectoryTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: Your test code here
		}

	};

	TEST_CLASS(ChangeViewTypeTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: Your test code here
		}

	};
}