#include "stdafx.h"
#include "CppUnitTest.h"
#include "TesterHeader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
	TEST_CLASS(CommandClass) {
public:
	/*
	TEST_METHOD(CommandAdd_Test) {

		list<Task*> *taskList = new list<Task*>;
		Task* individualTask;

		individualTask = new Task("read book" , 20160819 , 20160821 , 1300 , 1600 , "home");

		Command_Add command(taskList, individualTask);

		command.execute();

		list<Task*>::iterator listIter = (*taskList).begin();

		Assert::AreEqual(individualTask->getName(), (*listIter)->getName());
		Assert::AreEqual(individualTask->getLocation(), (*listIter)->getLocation());
		Assert::AreEqual(individualTask->getDate1(), (*listIter)->getDate1());
		Assert::AreEqual(individualTask->getDate2(), (*listIter)->getDate2());
		Assert::AreEqual(individualTask->getTime1(), (*listIter)->getTime1());
		Assert::AreEqual(individualTask->getTime2(), (*listIter)->getTime2());

	}
	};

	TEST_CLASS(ParserCLASS) {
public:
	//does a full comparison of expected and actual CommandPackage Object
	void compareCommandPackage(CommandPackage expected, CommandPackage actual) {
		Assert::AreEqual(expected.getCommandTypeString(), actual.getCommandTypeString());
		Assert::AreEqual(expected.getTask()->getName(), actual.getTask()->getName());
		Assert::AreEqual(expected.getTask()->getDate1(), actual.getTask()->getDate1());
		Assert::AreEqual(expected.getTask()->getDate2(), actual.getTask()->getDate2());
		Assert::AreEqual(expected.getTask()->getTime1(), actual.getTask()->getTime1());
		Assert::AreEqual(expected.getTask()->getTime2(), actual.getTask()->getTime2());
		Assert::AreEqual(expected.getTask()->getLocation(), actual.getTask()->getLocation());
		Assert::AreEqual(expected.getIndex(), actual.getIndex());
		Assert::AreEqual(expected.getDescription(), actual.getDescription());
		return;
	}

	TEST_METHOD(Parser_Add_Test_Simple) {
		CommandPackage expectedCommandPackage(ADD, Task("fly a plane", NO_DATE, NO_DATE, NO_TIME, NO_TIME, NO_LOCATION));
		Parser sut("fly a plane");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Add_Test_1Date) {
		CommandPackage expectedCommandPackage(ADD, Task("fly a plane", NO_DATE, 20010911, NO_TIME, NO_TIME, NO_LOCATION));
		Parser sut("fly a plane 11092001");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Add_Test_2Date) {
		CommandPackage expectedCommandPackage(ADD, Task("get a degree", 20140814, 20180515, NO_TIME, NO_TIME, NO_LOCATION));
		Parser sut("get a degree 14082014 15052018");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Add_Test_1Time) {
		CommandPackage expectedCommandPackage(ADD, Task("fly a plane", NO_DATE, NO_DATE, NO_TIME, 800, NO_LOCATION));
		Parser sut("fly a plane 0800");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Add_Test_2Time) {
		CommandPackage expectedCommandPackage(ADD, Task("fly a plane", NO_DATE, NO_DATE, 800, 1200, NO_LOCATION));
		Parser sut("fly a plane 0800 1200");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Add_Test_1Date_1Time) {
		CommandPackage expectedCommandPackage(ADD, Task("fly a plane", NO_DATE, 20010911, NO_TIME, 800, NO_LOCATION));
		Parser sut("fly a plane 11092001 0800");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Add_Test_1Time_1Date) {
		CommandPackage expectedCommandPackage(ADD, Task("fly a plane", NO_DATE, 20010911, NO_TIME, 800, NO_LOCATION));
		Parser sut("fly a plane 0800 11092001");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Add_Test_2Time_2Date) {
		CommandPackage expectedCommandPackage(ADD, Task("fly a plane", 20010911, 20010912, 800, 1200, NO_LOCATION));
		Parser sut("fly a plane 0800 1200 11092001 12092001");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Add_Test_Location) {
		CommandPackage expectedCommandPackage(ADD, Task("fly a plane", NO_DATE, NO_DATE, NO_TIME, NO_TIME, "world trade centre"));
		Parser sut("fly a plane @world trade centre");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Add_Test_Location_2Time_2Date) {
		CommandPackage expectedCommandPackage(ADD, Task("fly a plane", 20010911, 20010912, 800, 1200, "world trade centre"));
		Parser sut("fly a plane  @world trade centre 0800 1200 11092001 12092001");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Add_Test_2Time_2Date_Location) {
		CommandPackage expectedCommandPackage(ADD, Task("fly a plane", 20010911, 20010912, 800, 1200, "world trade centre"));
		Parser sut("fly a plane 0800 1200 11092001 12092001 @world trade centre");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Add_Test_Time_Date_Location_Jumbled) {
		CommandPackage expectedCommandPackage(ADD, Task("fly a plane", 20010911, 20010912, 800, 1200, "world trade centre"));
		Parser sut(" 0800 11092001 fly a plane @world trade centre 1200 12092001");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Add_Test_DateFormat2) {
		CommandPackage expectedCommandPackage(ADD, Task("graduate", NO_DATE, 20180615, NO_TIME, NO_TIME, NO_LOCATION));
		Parser sut("graduate 150618");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Add_Test_DateFormat3) {
		CommandPackage expectedCommandPackage(ADD, Task("celebrate christmas", NO_DATE, 20161225, NO_TIME, NO_TIME, NO_LOCATION));
		Parser sut("celebrate christmas 25/12");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Add_Test_DateFormat3_SingleDigitDay_SingleDigitMonth) {
		CommandPackage expectedCommandPackage(ADD, Task("celebrate christmas", NO_DATE, 20160706, NO_TIME, NO_TIME, NO_LOCATION));
		Parser sut("celebrate christmas 6/7");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Add_Test_DateFormat3_Invalid) {
		CommandPackage expectedCommandPackage(ADD, Task("celebrate christmas 2512/", NO_DATE, NO_DATE, NO_TIME, NO_TIME, NO_LOCATION));
		Parser sut("celebrate christmas 2512/");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Add_Test_DateFormat4) {
		CommandPackage expectedCommandPackage(ADD, Task("celebrate christmas", NO_DATE, 20161225, NO_TIME, NO_TIME, NO_LOCATION));
		Parser sut("celebrate christmas 25/12/16");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Add_Test_DateFormat4_SingleDigitDay_SingleDigitMonth) {
		CommandPackage expectedCommandPackage(ADD, Task("celebrate christmas", NO_DATE, 20160706, NO_TIME, NO_TIME, NO_LOCATION));
		Parser sut("celebrate christmas 6/7/16");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Add_Test_DateFormat4_FullYear) {
		CommandPackage expectedCommandPackage(ADD, Task("celebrate christmas", NO_DATE, 20161225, NO_TIME, NO_TIME, NO_LOCATION));
		Parser sut("celebrate christmas 25/12/2016");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Add_Test_DateFormat4_Invalid) {
		CommandPackage expectedCommandPackage(ADD, Task("celebrate christmas 25//2008", NO_DATE, NO_DATE, NO_TIME, NO_TIME, NO_LOCATION));
		Parser sut("celebrate christmas 25//2008");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Add_Test_InvalidDate_InvalidLeapDay) {
		CommandPackage expectedCommandPackage(ADD, Task("celebrate christmas 29022003", NO_DATE, NO_DATE, NO_TIME, NO_TIME, NO_LOCATION));
		Parser sut("celebrate christmas 29022003");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Add_Test_InvalidDate_InvalidMonth) {
		CommandPackage expectedCommandPackage(ADD, Task("celebrate christmas 31/4", NO_DATE, NO_DATE, NO_TIME, NO_TIME, NO_LOCATION));
		Parser sut("celebrate christmas 31/4");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Add_Test_1Time_AlternateFormat) {
		CommandPackage expectedCommandPackage(ADD, Task("fly a plane", NO_DATE, NO_DATE, NO_TIME, 800, NO_LOCATION));
		Parser sut("fly a plane 0800hrs");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Edit_Test_Simple) {
		CommandPackage expectedCommandPackage(EDIT, Task("fly a plane", NO_DATE, NO_DATE, NO_TIME, NO_TIME, NO_LOCATION),1);
		Parser sut("e 1 fly a plane");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Edit_Test_1Date_AlternateEditCommand) {
		CommandPackage expectedCommandPackage(EDIT, Task("fly a plane", NO_DATE, 20010911, NO_TIME, NO_TIME, NO_LOCATION), 2);
		Parser sut("c 2 fly a plane 11092001");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Edit_Test_2Date) {
		CommandPackage expectedCommandPackage(EDIT, Task(NO_NAME, 20140814, 20180515, NO_TIME, NO_TIME, NO_LOCATION), 1);
		Parser sut("e 1 14082014 15052018");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Edit_Test_1Time) {
		CommandPackage expectedCommandPackage(EDIT, Task(NO_NAME, NO_DATE, NO_DATE, NO_TIME, 800, NO_LOCATION), 1);
		Parser sut("e 1 0800");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Edit_Test_2Time) {
		CommandPackage expectedCommandPackage(EDIT, Task(NO_NAME, NO_DATE, NO_DATE, 800, 1200, NO_LOCATION), 1);
		Parser sut("e 1 0800 1200");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Edit_Test_1Date_1Time) {
		CommandPackage expectedCommandPackage(EDIT, Task(NO_NAME, NO_DATE, 20010911, NO_TIME, 800, NO_LOCATION), 1);
		Parser sut("e 1 11092001 0800");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Edit_Test_1Time_1Date) {
		CommandPackage expectedCommandPackage(EDIT, Task(NO_NAME, NO_DATE, 20010911, NO_TIME, 800, NO_LOCATION), 1);
		Parser sut("e 1 0800 11092001");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Edit_Test_2Time_2Date) {
		CommandPackage expectedCommandPackage(EDIT, Task(NO_NAME, 20010911, 20010912, 800, 1200, NO_LOCATION), 1);
		Parser sut("e 1 0800 1200 11092001 12092001");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Edit_Test_Location) {
		CommandPackage expectedCommandPackage(EDIT, Task(NO_NAME, NO_DATE, NO_DATE, NO_TIME, NO_TIME, "world trade centre"), 1);
		Parser sut("e 1 @world trade centre");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Edit_Test_Name_Location_2Time_2Date) {
		CommandPackage expectedCommandPackage(EDIT, Task("fly a plane", 20010911, 20010912, 800, 1200, "world trade centre"), 1);
		Parser sut("e 1 fly a plane @world trade centre 0800 1200 11092001 12092001");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Delete_Test_Standard) {
		CommandPackage expectedCommandPackage(DEL, Task(), 1);
		Parser sut("delete 1");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Delete_Test_Alternate) {
		CommandPackage expectedCommandPackage(DEL, Task(), 1);
		Parser sut("d 1");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Exit_Test_Standard) {
		CommandPackage expectedCommandPackage(EXIT);
		Parser sut("exit");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Exit_Test_Alternate) {
		CommandPackage expectedCommandPackage(EXIT);
		Parser sut("ex");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Display_Test_Standard) {
		CommandPackage expectedCommandPackage(DISPLAY);
		Parser sut("display");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Display_Test_Alternate1) {
		CommandPackage expectedCommandPackage(DISPLAY);
		Parser sut("view");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Display_Test_Alternate2) {
		CommandPackage expectedCommandPackage(DISPLAY);
		Parser sut("v");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Undo_Test_Standard) {
		CommandPackage expectedCommandPackage(UNDO);
		Parser sut("undo");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Undo_Test_Alternate) {
		CommandPackage expectedCommandPackage(UNDO);
		Parser sut("u");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_ChangeDirectory_Test_Standard) {
		CommandPackage expectedCommandPackage(SAVEDIRECTORY, Task(), NO_INDEX, "blahblahblah");
		Parser sut("cd blahblahblah");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_ChangeDirectory_Test_Alternate1) {
		CommandPackage expectedCommandPackage(SAVEDIRECTORY, Task(), NO_INDEX, "blahblahblah");
		Parser sut("change directory blahblahblah");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}
	
	TEST_METHOD(Parser_ChangeDirectory_Test_Alternate2) {
		CommandPackage expectedCommandPackage(SAVEDIRECTORY, Task(), NO_INDEX, "blahblahblah");
		Parser sut("c directory blahblahblah");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_ChangeDirectory_Test_Alternate3) {
		CommandPackage expectedCommandPackage(SAVEDIRECTORY, Task(), NO_INDEX, "blahblahblah");
		Parser sut("c d blahblahblah");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Search_Test_Standard) {
		CommandPackage expectedCommandPackage(SEARCH, Task(), NO_INDEX, "soul");
		Parser sut("search soul");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_Search_Test_Alternate) {
		CommandPackage expectedCommandPackage(SEARCH, Task(), NO_INDEX, "soul");
		Parser sut("s soul");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_ChangeViewType_Test_Standard) {
		CommandPackage expectedCommandPackage(VIEWTYPE, Task(), 1);
		Parser sut("view 1");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_ChangeViewType_Test_Alternate1) {
		CommandPackage expectedCommandPackage(VIEWTYPE, Task(), 1);
		Parser sut("v 1");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	TEST_METHOD(Parser_ChangeViewType_Test_Alternate2) {
		CommandPackage expectedCommandPackage(VIEWTYPE, Task(), 1);
		Parser sut("display 1");
		CommandPackage actualCommandPackage = *(sut.parse());
		compareCommandPackage(expectedCommandPackage, actualCommandPackage);
	}

	};

	TEST_CLASS(SettingCLASS) {
public:
	TEST_METHOD(Settings_TextFileNameMakerTest) {
		Settings Settings;
		string input = "text";
		string actualTexFileName;
		string expectedTextFileName = "text.txt";

		actualTexFileName = Settings.createValidTextFileNameString(input);
		Settings.updateTextFileName(input);

		Assert::AreEqual(expectedTextFileName,actualTexFileName);
		Assert::AreEqual(expectedTextFileName, Settings._textFileName);
	}

	TEST_METHOD(Settings_ChangeDirectoryTest) {
		Settings Settings;
		string input = "C:/Users/PeiChangHong/Documents/NUS Modules 14 I 15/Semester 4/CS2103/Core";
		string inputName = "mytextfile";
		string actualTexFileName;
		string expectedTextFileName = "mytextfile.txt";
		string expectedDirectory = "C:/Users/PeiChangHong/Documents/NUS Modules 14 I 15/Semester 4/CS2103/Core/";

		Assert::AreEqual(true,Settings.checkValidityOfDirectory(input));

		Settings.changeSaveDirectory(input);
		Settings.updateTextFileName(inputName);

		Assert::AreEqual(expectedTextFileName, Settings._textFileName);
		Assert::AreEqual(expectedDirectory, Settings._saveDirectory);

	}

	TEST_METHOD(Settings_GetDirectoryTest) {
		Settings Settings;
		Settings._textFileName = "text.txt";
		Settings._saveDirectory = "C:/my documents/";
		string expectedDirectory = "C:/my documents/text.txt";

		Assert::AreEqual(expectedDirectory, Settings.getSaveDirectory());
	}

	TEST_METHOD(Settings_LoadSaveTest) {
		Settings Setting;
		Settings testSetting;

		Setting._textFileName = "text.txt";
		Setting._saveDirectory = "C:/user/";
		string expectedTextFileName = "text.txt";
		string expectedDirectory = "C:/user/";

		Setting.openNewSettingFile();
		Setting.saveSettings();

		testSetting.loadSettings();

		Assert::AreEqual(expectedTextFileName, testSetting._textFileName);
		Assert::AreEqual(expectedDirectory, testSetting._saveDirectory);

		Setting._textFileName = Setting.VOID_STRING;
		Setting._saveDirectory = "C:/user/";
		expectedTextFileName = "";

		Setting.saveSettings();
		testSetting.loadSettings();

		Assert::AreEqual(expectedTextFileName, testSetting._textFileName);
		Assert::AreEqual(expectedDirectory, testSetting._saveDirectory);
	}
	};

	TEST_CLASS(UICLASS) {
public:
	TEST_METHOD(UI_GetTaskStringTypeDefault) {
		int i = 0;
		string actualString;
		list<Task*> ls;
		string expectedString[6] = { 
			"read book (home) 13:00 21/8/2016", 
			"read book (home) 13:00 19/8/2016 - 16:00 21/8/2016",             
			"read book (home) 21/9/2016",
			"read book (college) 1:00 - 2:00 22/9/2016",
			"read book 1:00 - 2:00 23/10/2016",
			"read book (college) <No deadline>"
		};

		ls.push_back(new Task("read book" , -1 , 20160821 , -1 , 1300 , "home"));
		ls.push_back(new Task("read book" , 20160819 , 20160821 , 1300 , 1600 , "home"));
		ls.push_back(new Task("read book" , -1 , 20160921 , -1 , -1 , "home"));
		ls.push_back(new Task("read book" , -1 , 20160922 , 100 , 200 , "college"));
		ls.push_back(new Task("read book" , -1 , 20161023 , 100 , 200 , ""));
		ls.push_back(new Task("read book" , -1 , -1 , -1 , -1 , "college"));
		UserInterface UI(&ls);

		list<Task*>::iterator listIter = ls.begin();

		while(listIter != ls.end()) {
			actualString = UI.getTaskString(*listIter , -1);
			Assert::AreEqual(expectedString[i], actualString);
			i++;
			listIter++;
		}

	}

	TEST_METHOD(UI_GetTaskStringType1) {
		int i = 0;
		string actualString;
		list<Task*> ls;
		string expectedStringType1[6] = { 
			"read book (home) 1:00 pm 21/8/2016", 
			"read book (home) 1:00 pm 19/8/2016 - 4:00 pm 21/8/2016",             
			"read book (home) 21/9/2016",
			"read book (college) 1:00 am - 2:00 am 22/9/2016",
			"read book 1:00 am - 2:00 am 23/10/2016",
			"read book (college) <No deadline>"
		};

		ls.push_back(new Task("read book" , -1 , 20160821 , -1 , 1300 , "home"));
		ls.push_back(new Task("read book" , 20160819 , 20160821 , 1300 , 1600 , "home"));
		ls.push_back(new Task("read book" , -1 , 20160921 , -1 , -1 , "home"));
		ls.push_back(new Task("read book" , -1 , 20160922 , 100 , 200 , "college"));
		ls.push_back(new Task("read book" , -1 , 20161023 , 100 , 200 , ""));
		ls.push_back(new Task("read book" , -1 , -1 , -1 , -1 , "college"));

		UserInterface UI(&ls);
		list<Task*>::iterator listIter = ls.begin();

		listIter = ls.begin();

		while(listIter != ls.end()) {
			actualString = UI.getTaskString(*listIter , 1);
			Assert::AreEqual(expectedStringType1[i], actualString);
			i++;
			listIter++;
		}

	}
	};

	TEST_CLASS(ViewTypeCLASS) {
public:
	TEST_METHOD(ViewType_CreateDisplayList) {
		vector<string> actualDisplayList;
		int i = 0;
		ViewType testView;
		list<Task*> ls;
		string expectedString[6] = { 
			"1. read book (home) 13:00 21/8/2016", 
			"2. read book (home) 13:00 19/8/2016 - 16:00 21/8/2016",             
			"3. read book (home) 21/9/2016",
			"4. read book (college) 1:00 - 2:00 22/9/2016",
			"5. read book 1:00 - 2:00 23/10/2016",
			"6. read book (college) <No deadline>"
		};

		ls.push_back(new Task("read book" , -1 , 20160821 , -1 , 1300 , "home"));
		ls.push_back(new Task("read book" , 20160819 , 20160821 , 1300 , 1600 , "home"));
		ls.push_back(new Task("read book" , -1 , 20160921 , -1 , -1 , "home"));
		ls.push_back(new Task("read book" , -1 , 20160922 , 100 , 200 , "college"));
		ls.push_back(new Task("read book" , -1 , 20161023 , 100 , 200 , ""));
		ls.push_back(new Task("read book" , -1 , -1 , -1 , -1 , "college"));
		testView._taskList = &ls;

		actualDisplayList = testView.createDisplayList();

		vector<string>::iterator displayListIter = actualDisplayList.begin();

		while(displayListIter != actualDisplayList.end()) {
			Assert::AreEqual(*displayListIter  , expectedString[i]);
			i++;
			displayListIter++;
		}

	}

	TEST_METHOD(ViewType_CreateSearchList) {
		vector<string> actualDisplayList;
		int i = 0;
		ViewType testView;
		list<Task*> ls;
		string expectedString[6] = { 
			"1. read book (home) 13:00 21/8/2016", 
			"2. read book (home) 13:00 19/8/2016 - 16:00 21/8/2016",             
			"3. read book (home) 21/9/2016",
			"4. read book (college) 1:00 - 2:00 22/9/2016",
			"5. read book 1:00 - 2:00 23/10/2016",
			"6. read book (college) <No deadline>"
		};

		ls.push_back(new Task("read book" , -1 , 20160821 , -1 , 1300 , "home"));
		ls.push_back(new Task("read book" , 20160819 , 20160821 , 1300 , 1600 , "home"));
		ls.push_back(new Task("read book" , -1 , 20160921 , -1 , -1 , "home"));
		ls.push_back(new Task("read book" , -1 , 20160922 , 100 , 200 , "college"));
		ls.push_back(new Task("read book" , -1 , 20161023 , 100 , 200 , ""));
		ls.push_back(new Task("read book" , -1 , -1 , -1 , -1 , "college"));
		testView._taskList = &ls;

		actualDisplayList = testView.createSearchList();

		vector<string>::iterator displayListIter = actualDisplayList.begin();

		while(displayListIter != actualDisplayList.end()) {
			Assert::AreEqual(*displayListIter  , expectedString[i]);
			i++;
			displayListIter++;
		}

	}
	};

	TEST_CLASS(ViewType0CLASS) {
public:
	TEST_METHOD(ViewType1_CreateDisplayList) {
		vector<string> actualDisplayList;
		int i = 0;
		ViewType *testView;
		list<Task*> ls;
		string expectedString[8] = { 
			"Today's date is 21/8/2016",
			"1. read book (home) 1:00 pm 21/8/2016", 
			"2. read book (home) 1:00 pm 19/8/2016 - 4:00 pm 21/8/2016",             
			" ",
			"3. read book (home) 21/9/2016",
			"4. read book (college) 1:00 am - 2:00 am 22/9/2016",
			"5. read book 1:00 am - 2:00 am 23/10/2016",
			"6. read book (college) <No deadline>"
		};

		ls.push_back(new Task("read book" , -1 , 20160821 , -1 , 1300 , "home"));
		ls.push_back(new Task("read book" , 20160819 , 20160821 , 1300 , 1600 , "home"));
		ls.push_back(new Task("read book" , -1 , 20160921 , -1 , -1 , "home"));
		ls.push_back(new Task("read book" , -1 , 20160922 , 100 , 200 , "college"));
		ls.push_back(new Task("read book" , -1 , 20161023 , 100 , 200 , ""));
		ls.push_back(new Task("read book" , -1 , -1 , -1 , -1 , "college"));

		testView = new ViewType1(&ls , 20160821); //initiate marker = 0

		actualDisplayList = testView->createDisplayList();

		vector<string>::iterator displayListIter = actualDisplayList.begin();

		while(displayListIter != actualDisplayList.end()) {
			Assert::AreEqual(*displayListIter  , expectedString[i]);
			i++;
			displayListIter++;
		}

	}

	TEST_METHOD(ViewType1_CreateSearchList) {
		vector<string> actualDisplayList;
		int i = 0;
		ViewType1 testView;
		list<Task*> ls;
		string expectedString[6] = { 
			"1. read book (home) 1:00 pm 21/8/2016", 
			"2. read book (home) 1:00 pm 19/8/2016 - 4:00 pm 21/8/2016",             
			"3. read book (home) 21/9/2016",
			"4. read book (college) 1:00 am - 2:00 am 22/9/2016",
			"5. read book 1:00 am - 2:00 am 23/10/2016",
			"6. read book (college) <No deadline>"
		};

		ls.push_back(new Task("read book" , -1 , 20160821 , -1 , 1300 , "home"));
		ls.push_back(new Task("read book" , 20160819 , 20160821 , 1300 , 1600 , "home"));
		ls.push_back(new Task("read book" , -1 , 20160921 , -1 , -1 , "home"));
		ls.push_back(new Task("read book" , -1 , 20160922 , 100 , 200 , "college"));
		ls.push_back(new Task("read book" , -1 , 20161023 , 100 , 200 , ""));
		ls.push_back(new Task("read book" , -1 , -1 , -1 , -1 , "college"));
		testView._taskList = &ls;

		actualDisplayList = testView.createSearchList();

		vector<string>::iterator displayListIter = actualDisplayList.begin();

		while(displayListIter != actualDisplayList.end()) {
			Assert::AreEqual(expectedString[i], *displayListIter);
			i++;
			displayListIter++;
		}

	}
	*/
	};
}