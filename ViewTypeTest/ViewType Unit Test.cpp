#include "stdafx.h"
#include "CppUnitTest.h"
#include "TesterHeader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ViewTypeTest{		
    TEST_CLASS(ViewTypeCLASS) {
public:
    TEST_METHOD(ViewType_getTaskString) {
        Task* task;
        ViewType testView;
        string expectedString = "read book (home) 13:00 19/8/2016 - 16:00 21/8/2016";
        string actualString;

        task = new Task("read book" , 20160819 , 20160821 , 1300 , 1600 , "home");
        actualString = testView.getTaskString(task);
        Assert::AreEqual(actualString, expectedString);
    }

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

        ls.push_back(new Task("read book" , NO_DATE , 20160821 , NO_TIME , 1300 , "home"));
        ls.push_back(new Task("read book" , 20160819 , 20160821 , 1300 , 1600 , "home"));
        ls.push_back(new Task("read book" , NO_DATE , 20160921 , NO_TIME , NO_TIME , "home"));
        ls.push_back(new Task("read book" , NO_DATE , 20160922 , 100 , 200 , "college"));
        ls.push_back(new Task("read book" , NO_DATE , 20161023 , 100 , 200 , ""));
        ls.push_back(new Task("read book" , NO_DATE , NO_DATE , NO_TIME , NO_TIME , "college"));
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

        ls.push_back(new Task("read book" , NO_DATE , 20160821 , NO_TIME , 1300 , "home"));
        ls.push_back(new Task("read book" , 20160819 , 20160821 , 1300 , 1600 , "home"));
        ls.push_back(new Task("read book" , NO_DATE , 20160921 , NO_TIME , NO_TIME , "home"));
        ls.push_back(new Task("read book" , NO_DATE , 20160922 , 100 , 200 , "college"));
        ls.push_back(new Task("read book" , NO_DATE , 20161023 , 100 , 200 , ""));
        ls.push_back(new Task("read book" , NO_DATE , NO_DATE , NO_TIME , NO_TIME , "college"));
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

    TEST_CLASS(ViewType1CLASS) {
public:
    TEST_METHOD(ViewType1_getTaskString) {
        Task* task;
        ViewType1 testView;
        string expectedString = "read book (home) 1:00 pm 19/8/2016 - 4:00 pm 21/8/2016";
        string actualString;

        task = new Task("read book" , 20160819 , 20160821 , 1300 , 1600 , "home");
        actualString = testView.getTaskString(task);
        Assert::AreEqual(actualString, expectedString);
    }

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

        ls.push_back(new Task("read book" , NO_DATE , 20160821 , NO_TIME , 1300 , "home"));
        ls.push_back(new Task("read book" , 20160819 , 20160821 , 1300 , 1600 , "home"));
        ls.push_back(new Task("read book" , NO_DATE , 20160921 , NO_TIME , NO_TIME , "home"));
        ls.push_back(new Task("read book" , NO_DATE , 20160922 , 100 , 200 , "college"));
        ls.push_back(new Task("read book" , NO_DATE , 20161023 , 100 , 200 , ""));
        ls.push_back(new Task("read book" , NO_DATE , NO_DATE , NO_TIME , NO_TIME , "college"));

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

        ls.push_back(new Task("read book" , NO_DATE , 20160821 , NO_TIME , 1300 , "home"));
        ls.push_back(new Task("read book" , 20160819 , 20160821 , 1300 , 1600 , "home"));
        ls.push_back(new Task("read book" , NO_DATE , 20160921 , NO_TIME , NO_TIME , "home"));
        ls.push_back(new Task("read book" , NO_DATE , 20160922 , 100 , 200 , "college"));
        ls.push_back(new Task("read book" , NO_DATE , 20161023 , 100 , 200 , ""));
        ls.push_back(new Task("read book" , NO_DATE , NO_DATE , NO_TIME , NO_TIME , "college"));
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

    TEST_CLASS(ViewType2CLASS) {
public:
    TEST_METHOD(ViewType2_getTaskString) {
        Task* task;
        ViewType2 testView;
        string expectedString = "read book (home) 1:00 pm 19-Aug - 4:00 pm 21-Aug";
        string actualString;

        task = new Task("read book" , 20160819 , 20160821 , 1300 , 1600 , "home");
        actualString = testView.getTaskString(task);
        Assert::AreEqual(actualString, expectedString);
    }

    TEST_METHOD(ViewType2_CreateDisplayList) {
        vector<string> actualDisplayList;
        int i = 0;
        ViewType *testView;
        list<Task*> ls;
        string expectedString[8] = { 
            "Today's date is 21-Aug",
            "1. read book (home) 1:00 pm 21-Aug", 
            "2. read book (home) 1:00 pm 19-Aug - 4:00 pm 21-Aug",
            " ",
            "3. read book (home) 21-Sep",
            "4. read book (college) 1:00 am - 2:00 am 22-Sep",
            "5. read book 1:00 am - 2:00 am 23-Oct",
            "6. read book (college) <No deadline>"
        };

        ls.push_back(new Task("read book" , NO_DATE , 20160821 , NO_TIME , 1300 , "home"));
        ls.push_back(new Task("read book" , 20160819 , 20160821 , 1300 , 1600 , "home"));
        ls.push_back(new Task("read book" , NO_DATE , 20160921 , NO_TIME , NO_TIME , "home"));
        ls.push_back(new Task("read book" , NO_DATE , 20160922 , 100 , 200 , "college"));
        ls.push_back(new Task("read book" , NO_DATE , 20161023 , 100 , 200 , ""));
        ls.push_back(new Task("read book" , NO_DATE , NO_DATE , NO_TIME , NO_TIME , "college"));

        testView = new ViewType2(&ls , 20160821); //initiate marker = 0

        actualDisplayList = testView->createDisplayList();

        vector<string>::iterator displayListIter = actualDisplayList.begin();

        while(displayListIter != actualDisplayList.end()) {
            Assert::AreEqual(*displayListIter  , expectedString[i]);
            i++;
            displayListIter++;
        }

    }

    TEST_METHOD(ViewType2_CreateSearchList) {
        vector<string> actualDisplayList;
        int i = 0;
        ViewType2 testView;
        list<Task*> ls;
        string expectedString[6] = { 
            "1. read book (home) 1:00 pm 21-Aug", 
            "2. read book (home) 1:00 pm 19-Aug - 4:00 pm 21-Aug",             
            "3. read book (home) 21-Sep",
            "4. read book (college) 1:00 am - 2:00 am 22-Sep",
            "5. read book 1:00 am - 2:00 am 23-Oct",
            "6. read book (college) <No deadline>"
        };

        ls.push_back(new Task("read book" , NO_DATE , 20160821 , NO_TIME , 1300 , "home"));
        ls.push_back(new Task("read book" , 20160819 , 20160821 , 1300 , 1600 , "home"));
        ls.push_back(new Task("read book" , NO_DATE , 20160921 , NO_TIME , NO_TIME , "home"));
        ls.push_back(new Task("read book" , NO_DATE , 20160922 , 100 , 200 , "college"));
        ls.push_back(new Task("read book" , NO_DATE , 20161023 , 100 , 200 , ""));
        ls.push_back(new Task("read book" , NO_DATE , NO_DATE , NO_TIME , NO_TIME , "college"));
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