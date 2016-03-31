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
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, NO_TIME, 2005));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Add_2Time)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 2005 hrs 2100hrs");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, 2005, 2100));
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
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, NO_TIME, 2359));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_ValidTime_LowerBorder)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 0000hrs");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, NO_TIME, 0));
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
		
		TEST_METHOD(Parser_TimeFormatA_4Digit)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 0000hrs");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, NO_TIME, 0));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeFormatA_3Digit)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 800hrs");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, NO_TIME, 800));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeFormatB_1Digit)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 1am");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, NO_TIME, 100));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeFormatB_2Digit)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 11am");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, NO_TIME, 1100));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeFormatB_3Digit)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 130am");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, NO_TIME, 130));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeFormatB_4Digit)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 1130am");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, NO_TIME, 1130));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeFormatB_PMTest)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 1130pm");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, NO_TIME, 2330));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeFormatB_12AM)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 1230am");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, NO_TIME, 30));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeFormatB_12PM)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 1230pm");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, NO_TIME, 1230));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}
		
		TEST_METHOD(Parser_TimeFormatB_NonsenseMeridiemTime)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 1330pm");
			Command* expected = new Command_Add(new Task("go home 1330pm"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeFormatC_Scenario1)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 12th feb 1330");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, 20160212, NO_TIME, 1330));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeFormatC_Scenario2)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home feb 12 1330");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, 20160212, NO_TIME, 1330));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeFormatC_Scenario3)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home feb 12 17 1330");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, 20170212, NO_TIME, 1330));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeRangeFormatA_Standard)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 8-1130pm");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, 2000, 2330));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeRangeFormatA_InversedMeridiem)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 8-230pm");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, 800, 1430));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeRangeFormatA_InversedMeridiem_NextDay)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 8-230am");
			Command* expected = new Command_Add(new Task("go home", DATE, DATE+1, 2000, 230));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeRangeFormatA_XXTo12am)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 8-1230am");
			Command* expected = new Command_Add(new Task("go home", DATE, DATE+1, 2000, 30));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeRangeFormatA_XXTo12pm)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 8-1230pm");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, 800, 1230));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeRangeFormatA_12ToXXam)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 12-1130am");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, 0000, 1130));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeRangeFormatA_12ToXXpm)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 1215-1130pm");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, 1215, 2330));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeRangeFormatA_12To12am)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 12-1230am");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, 0, 30));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeRangeFormatA_12To12pm)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 1215-1230pm");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, 1215, 1230));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeRangeFormatA_12To12am_Reversed)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 1245-1230am");
			Command* expected = new Command_Add(new Task("go home", DATE, DATE+1, 1245, 30));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeRangeFormatA_12To12pm_Reversed)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 1245-1230pm");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, 45, 1230));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_TimeRangeFormatB)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home 800-1130hrs");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE, 800, 1130));
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
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE+1));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateFormatE_Type3)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home yesterday");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, DATE-1));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateFormatE_Type4)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home next sunday");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, 20160410));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateFormatE_Type5)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home sat");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, 20160402));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateFormatE_Type6)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home next week");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, 20160410));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateFormatE_Type7)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home this week");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, 20160403));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_DateFormatE_Type8)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home this sun");
			Command* expected = new Command_Add(new Task("go home", NO_DATE, 20160403));
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

		TEST_METHOD(Parser_DateRangeFormatB_Type1)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("go home feb 17th-19th");
			Command* expected = new Command_Add(new Task("go home", 20160217, 20160219));
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

		TEST_METHOD(Parser_Edit_Valid_NaturalLanguage)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("edit 1 to go home");
			Command* expected = new Command_Edit(1, new Task("go home"));
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Edit_LastIndex_NaturalLanguage)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("edit to go home");
			Command* expected = new Command_Edit(0, new Task("go home"));
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

	TEST_CLASS(DeleteTest)
	{
	public:
		TEST_METHOD(Parser_Delete_Valid_LastIndex)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("d");
			Command* expected = new Command_Delete(0);
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}

		TEST_METHOD(Parser_Delete_Valid)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("d 1");
			Command* expected = new Command_Delete(1);
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
			Command* actual = sut->parse("view 2");
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

		TEST_METHOD(Parser_ChangeDirectory_InValid_Type2)
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

		TEST_METHOD(Parser_Search_InValid)
		{
			Parser* sut = Parser::getInstance();
			Command* actual = sut->parse("s");
			Command* expected = new Command_Invalid();
			Assert::AreEqual(expected->getStringForm(),actual->getStringForm());
		}
	};
}