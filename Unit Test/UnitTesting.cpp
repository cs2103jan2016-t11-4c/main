#include "stdafx.h"
#include "CppUnitTest.h"
#include "TesterHeader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    TEST_CLASS(CommandClass) {
public:
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
    TEST_METHOD(Parser_Test) {
	
    CommandPackage expectedCommandObject(ADD, Task("fly a plane",0,11092001,-1,-1),0,"");
    Parser sut("fly a plane 11092001");
	CommandPackage actualCommandObject = *(sut.parse());

	Assert::AreEqual(actualCommandObject.getCommandTypeString(), expectedCommandObject.getCommandTypeString());
	Assert::AreEqual(actualCommandObject.getTask()->getName(), expectedCommandObject.getTask()->getName());
	Assert::AreEqual(actualCommandObject.getTask()->getDate1(), expectedCommandObject.getTask()->getDate1());
	Assert::AreEqual(actualCommandObject.getTask()->getDate2(), expectedCommandObject.getTask()->getDate2());
	Assert::AreEqual(actualCommandObject.getTask()->getTime1(), expectedCommandObject.getTask()->getTime1());
	Assert::AreEqual(actualCommandObject.getTask()->getTime2(), expectedCommandObject.getTask()->getTime2());
	Assert::AreEqual(actualCommandObject.getTask()->getLocation(), expectedCommandObject.getTask()->getLocation());
	Assert::AreEqual(actualCommandObject.getIndex(), expectedCommandObject.getIndex());
	Assert::AreEqual(actualCommandObject.getDescription(), expectedCommandObject.getDescription());
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

    TEST_METHOD(UI_GetTaskStringType0) {
        int i = 0;
        string actualString;
        list<Task*> ls;
        string expectedStringType0[6] = { 
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
            actualString = UI.getTaskString(*listIter , 0);
            Assert::AreEqual(expectedStringType0[i], actualString);
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
    TEST_METHOD(ViewType0_CreateDisplayList) {
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

        testView = new ViewType0(&ls , 20160821); //initiate marker = 0

        actualDisplayList = testView->createDisplayList();

        vector<string>::iterator displayListIter = actualDisplayList.begin();

        while(displayListIter != actualDisplayList.end()) {
            Assert::AreEqual(*displayListIter  , expectedString[i]);
            i++;
            displayListIter++;
        }

    }

    TEST_METHOD(ViewType0_CreateSearchList) {
        vector<string> actualDisplayList;
        int i = 0;
        ViewType0 testView;
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
    };
}