#include "stdafx.h"
#include "CppUnitTest.h"
#include "TesterHeader.h"

string testStringDriver[5] = { 
    "Attend dance performance @museum 1/4 730pm", 
    "Conduct V0.3 demo on 31 march 11am",
    "Sleep by 1200am 1 jan",
    "Presentation for IE2150 from 11/4 to 12/4",
    "Study hard"
}; 

string testerClear = "clear";

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTest {	
    TEST_CLASS(Integration) {
public:
	
    TEST_METHOD(_Integration_Command_Add_Feedback_V0) {
        UserInterface sut;
        Command* testCommand;
        int testViewType = 0;
        int i = 0;
        string actualString;
        string expectedString[5] = {
            "Added \"Attend dance performance (museum) (19:30 1/4/2016)\" into doMe.txt",
            "Added \"Conduct V0.3 demo (11:00 31/3/2016)\" into doMe.txt",
            "Added \"Sleep (0:00 1/1/2016)\" into doMe.txt",
            "Added \"Presentation for IE2150 (11/4/2016 - 12/4/2016)\" into doMe.txt",
            "Added \"Study hard <No deadline>\" into doMe.txt"
        };

        //case: Addition of task
        //Test Parser + Command_Add + ViewType(default) + Command_Feedback of add
        for(i = 0; i < 5; i++) {
            testCommand = sut._logic->executeCommand(testStringDriver[i]);
            actualString = (sut._commandFeedback)->getCommandFeedback(testCommand, VALID_MESSAGE, testViewType);

            Assert::AreEqual(expectedString[i], actualString);
        }
    }
    
    TEST_METHOD(_Integration_Command_Clear_Feedback_V0) {
        UserInterface sut;
        Command* testCommand;
        int testViewType = 0;
        int i = 0;
        string actualString;
        string expectedString = "All tasks in view cleared.";

        for(i = 0; i < 5; i++) {
            sut._logic->executeCommand(testStringDriver[i]);
        }

        //case: Clearing of task
        //Test Parser + Command_Clear + ViewType(default) + Command_Feedback of clear
        testCommand = sut._logic->executeCommand(testerClear);
        actualString = (sut._commandFeedback)->getCommandFeedback(testCommand, VALID_MESSAGE, testViewType);
        Assert::AreEqual(expectedString, actualString);

    }

    TEST_METHOD(_Integration_Command_Delete_Feedback_V1) {
        UserInterface sut;
        Command* testCommand;
        int testViewType = 1;
        int i = 0;
        string actualString;
        string expectedString[5] = {
            "Deleted \"Study hard <No deadline>\" from doMe.txt",
            "Deleted \"Sleep (12:00am 1-Jan)\" from doMe.txt",
            "Deleted \"Attend dance performance (museum) (7:30pm 1-Apr)\" from doMe.txt"
        };
        string testerDelete[3] = {
            "delete 1",
            "delete 1",
            "delete 2"
        };

        sut._logic->executeCommand(testerClear);
        for(i = 0; i < 5; i++) {
            sut._logic->executeCommand(testStringDriver[i]);
        }

        //case: Deletion of task
        //Test Parser + Command_Delete + ViewType(1) + Command_Feedback of delete
        for(i = 0; i < 3; i++) {
            testCommand = sut._logic->executeCommand(testerDelete[i]);
            actualString = (sut._commandFeedback)->getCommandFeedback(testCommand, VALID_MESSAGE, testViewType);

            Assert::AreEqual(expectedString[i], actualString);
        }
    }
    
    TEST_METHOD(_Integration_Command_Edit_Feedback_V2) {
        UserInterface sut;
        Command* testCommand;
        int testViewType = 2;
        int i = 0;
        string actualString;
        string expectedString[5] = {
            "Sleep (12:00am 1-Jan)",
            "Conduct V0.3 demo (11:00am 31-Mar)",
            "Study harder (4-Apr)",
            "Attend dance performance (museum) (7:30pm 5-Apr)",
            "Presentation for IE2150 (11-Apr - 12-Apr)"  
        };
        string expectedFeedback[2] = {
            "Editted task to \"Study harder (4-Apr)\".",
            "Editted task to \"Attend dance performance (museum) (7:30pm 5-Apr)\"."
        };
        string testerEdit[2] = {
            "edit 1 Study harder 4/4",
            "edit 3 5/4"
        };

        sut._logic->executeCommand(testerClear);
        for(i = 0; i < 5; i++) {
            sut._logic->executeCommand(testStringDriver[i]);
        }

        for(i = 0; i < 2; i++) {
            testCommand = sut._logic->executeCommand(testerEdit[i]);
            actualString = (sut._commandFeedback)->getCommandFeedback(testCommand, VALID_MESSAGE, testViewType);
            Assert::AreEqual(expectedFeedback[i], actualString);
        }
        //case: Editing of task
        //Test Parser + Command_Edit + ViewType(2) + Command_Feedback of edit
        list<Task*>::iterator taskListIter = (*(sut._taskList)).begin();
        i = 0;
        while(taskListIter != (*(sut._taskList)).end()) {
            actualString = (sut._commandFeedback)->getTaskString(*taskListIter, testViewType);
            Assert::AreEqual(expectedString[i], actualString);
            taskListIter++;
            i++;
        }
    }
	
    };
}