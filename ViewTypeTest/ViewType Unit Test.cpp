#include "stdafx.h"
#include "CppUnitTest.h"
#include "TesterHeader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ViewTypeTest
{		
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
	
	};
}