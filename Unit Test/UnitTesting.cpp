#include "stdafx.h"
#include "CppUnitTest.h"
#include "TesterHeader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {		
    TEST_CLASS(SettingTest) {
public:
	/*
	TEST_METHOD(ParserTest) {
		CommandPackage expectedAddObject(ADD, Task("fly a plane",0,11092001,-1,-1),0,"");
		Parser sut("fly a plane 11092001");

		Assert::AreEqual(sut.parse(),&expectedAddObject);
	}
	*/
    TEST_METHOD(SettingsTextFileNameMakerTest) {
        Settings Settings;
        string input = "text";
        string actualTexFileName;
        string expectedTextFileName = "text.txt";

        actualTexFileName = Settings.createValidTextFileNameString(input);
        Settings.updateTextFileName(input);

        Assert::AreEqual(expectedTextFileName,actualTexFileName);
        Assert::AreEqual(expectedTextFileName, Settings._textFileName);
    }

    TEST_METHOD(SettingsChangeDirectoryTest) {
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

    TEST_METHOD(SettingsGetDirectoryTest) {
        Settings Settings;
        Settings._textFileName = "text.txt";
        Settings._saveDirectory = "C:/my documents/";
        string expectedDirectory = "C:/my documents/text.txt";

        Assert::AreEqual(expectedDirectory, Settings.getSaveDirectory());
    }

    TEST_METHOD(SettingsLoadSaveTest) {
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
    TEST_METHOD(UIGetTaskStringTypeDefault) {
        UserInterface UI;
        UI._defaultViewType = -1;
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

        list<Task*>::iterator listIter = ls.begin();

        while(listIter != ls.end()) {
            actualString = UI.getTaskString(*listIter , UI._defaultViewType);
            Assert::AreEqual(expectedString[i], actualString);
            i++;
            listIter++;
        }

    }

    TEST_METHOD(UIGetTaskStringType0) {
        UserInterface UI;
        UI._defaultViewType = 0;
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

        list<Task*>::iterator listIter = ls.begin();

        UI._defaultViewType = 0;

        listIter = ls.begin();

        while(listIter != ls.end()) {
            actualString = UI.getTaskString(*listIter , UI._defaultViewType);
            Assert::AreEqual(expectedStringType0[i], actualString);
            i++;
            listIter++;
        }

    }
    };

    TEST_CLASS(ViewTypeCLASS) {
public:
    TEST_METHOD(ViewTypeCreateDisplayList) {
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

    TEST_METHOD(ViewTypeCreateSearchList) {
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
    TEST_METHOD(ViewType0CreateDisplayList) {
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

    TEST_METHOD(ViewType0CreateSearchList) {
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