#include "stdafx.h"
#include "CppUnitTest.h"

#include "Commons.cpp"
#include "Exception_InvalidCommand.cpp"
#include "Exception_FileCannotOpen.cpp"
#include "Exception_FirstTimeUser.cpp"
#include "Exception_CorruptedFile.cpp"
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
#include "Command_Edit.cpp"
#include "Command_Exit.cpp"
#include "Command_Invalid.cpp"
#include "Command_SaveDirectory.cpp"
#include "Command_Search.cpp"
#include "Command_Undo.cpp"
#include "Command_ViewType.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace doMeTests_Command
{		
	TEST_CLASS(Command_AddTests)
	{
	public:

		TEST_METHOD(Command_AddTest_Execute_Task) {
			Task* task = new Task();
			Memory* memory = Memory::getInstance();
			list<Task*> expectedTaskList = *(memory->ramGetTaskList());
			Command_Add command(task);
			bool executionStatus;

			executionStatus = command.execute();

			Assert::AreEqual(true, executionStatus);
		}

		TEST_METHOD(Command_AddTest_Execute_NULL) {
			Memory* memory = Memory::getInstance();
			list<Task*> expectedTaskList = *(memory->ramGetTaskList());
			Command_Add command(NULL);
			bool executionStatus;

			executionStatus = command.execute();

			Assert::AreEqual(false, executionStatus);
		}
	};

	TEST_CLASS(Command_DeleteTests) {
		TEST_METHOD(Command_DeleteTest_outOfRange_true_negativeNumber) {
			Memory* memory = Memory::getInstance();
			vector<int> deleteList;
			Task* task = new Task();

			for(int i = 0 ; i < 5; i++) {
				memory->ramAdd(task);
			}

			deleteList.push_back(-1);
			Command_Clear* command = new Command_Clear(&deleteList);
			bool outOfRange = command->outOfRange();
			Assert::AreEqual(true, outOfRange);
		}

		TEST_METHOD(Command_DeleteTest_outOfRange_true_tooHigh) {
			Memory* memory = Memory::getInstance();
			vector<int> deleteList;
			Task* task = new Task();

			for(int i = 0 ; i < 5; i++) {
				memory->ramAdd(task);
			}

			deleteList.push_back(6);
			Command_Clear* command = new Command_Clear(&deleteList);
			bool outOfRange = command->outOfRange();
			Assert::AreEqual(true, outOfRange);
		}

		TEST_METHOD(Command_DeleteTest_outOfRange_false_singleIndexZero) {
			Memory* memory = Memory::getInstance();
			vector<int> deleteList;
			Task* task = new Task();

			for(int i = 0 ; i < 5; i++) {
				memory->ramAdd(task);
			}

			deleteList.push_back(0);
			Command_Clear* command = new Command_Clear(&deleteList);
			bool outOfRange = command->outOfRange();
			Assert::AreEqual(false, outOfRange);
		}

		TEST_METHOD(Command_DeleteTest_outOfRange_false_singleMaxValidIndex) {
			Memory* memory = Memory::getInstance();
			vector<int> deleteList;
			Task* task = new Task();

			for(int i = 0 ; i < 5; i++) {
				memory->ramAdd(task);
			}

			deleteList.push_back(5);
			Command_Clear* command = new Command_Clear(&deleteList);
			bool outOfRange = command->outOfRange();
			Assert::AreEqual(false, outOfRange);
		}

		TEST_METHOD(Command_DeleteTest_outOfRange_false_MultipleAllValid) {
			Memory* memory = Memory::getInstance();
			vector<int> deleteList;
			Task* task = new Task();

			for(int i = 0 ; i < 5; i++) {
				memory->ramAdd(task);
			}

			for(int i = 0 ; i < 6; i++) {
				deleteList.push_back(i);
			}

			Command_Clear* command = new Command_Clear(&deleteList);
			bool outOfRange = command->outOfRange();
			Assert::AreEqual(false, outOfRange);
		}

		TEST_METHOD(Command_DeleteTest_clearAllTasks) {
			Memory* memory = Memory::getInstance();
			vector<int> deleteList;
			Task* task = new Task();

			for(int i = 0 ; i < 5; i++) {
				memory->ramAdd(task);
			}

			Command_Clear* command = new Command_Clear(&deleteList);

			command->execute();

			int taskListSize = memory->ramGetSize();

			Assert::AreEqual(0, taskListSize);
		}
		TEST_METHOD(Command_DeleteTest_clearSelectedTasks_Single) {
			Memory* memory = Memory::getInstance();
			vector<int> deleteList;

			for(int i = 1 ; i < 6; i++) {
				memory->ramAdd(new Task(to_string(i),-1,-1,-1,-1,"",0));
			}

			deleteList.push_back(1);

			Command_Clear* command = new Command_Clear(&deleteList);

			command->execute();
			list<Task*>* taskList = memory->ramGetTaskList();
			list<Task*>* expectedTaskList;

			for(int i = 2; i < 6; i++) {
				expectedTaskList->push_back(new Task(to_string(i),-1,-1,-1,-1,"",0));
			}

			list<Task*>::iterator taskListIter = taskList->begin();
			list<Task*>::iterator expectedTaskListIter = expectedTaskList->begin();

			Assert::AreEqual(taskList->size(), expectedTaskList->size());

			while(taskListIter != taskList->end() && expectedTaskListIter != expectedTaskList->end()) {
				Assert::AreEqual((*taskListIter)->getName(), (*expectedTaskListIter)->getName());
			}
		}


		TEST_METHOD(Command_DeleteTest_clearSelectedTasks_Multiple) {
			Memory* memory = Memory::getInstance();
			vector<int> deleteList;

			for(int i = 1 ; i < 6; i++) {
				memory->ramAdd(new Task(to_string(i),-1,-1,-1,-1,"",0));
			}

			deleteList.push_back(1);
			deleteList.push_back(3);
			deleteList.push_back(5);

			Command_Clear* command = new Command_Clear(&deleteList);

			command->execute();
			list<Task*>* taskList = memory->ramGetTaskList();
			list<Task*>* expectedTaskList;

			expectedTaskList->push_back(new Task(to_string(2),-1,-1,-1,-1,"",0));
			expectedTaskList->push_back(new Task(to_string(4),-1,-1,-1,-1,"",0));			

			list<Task*>::iterator taskListIter = taskList->begin();
			list<Task*>::iterator expectedTaskListIter = expectedTaskList->begin();

			Assert::AreEqual(taskList->size(), expectedTaskList->size());

			while(taskListIter != taskList->end() && expectedTaskListIter != expectedTaskList->end()) {
				Assert::AreEqual((*taskListIter)->getName(), (*expectedTaskListIter)->getName());
			}
		}
	};
}