#include "stdafx.h"
#include "CppUnitTest.h"

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

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace doMeTests_Command
{		
	TEST_CLASS(Command_AddTests)
	{
	public:

		TEST_METHOD(Command_AddTest_Execute_Task)
		{
			Task* task = new Task();
			Memory* memory = Memory::getInstance();
			list<Task*> expectedTaskList = *(memory->ramGetTaskList());
			Command_Add command(task);
			bool executionStatus;

			executionStatus = command.execute();

			Assert::AreEqual(true, executionStatus);
		}

		TEST_METHOD(Command_AddTest_Execute_NULL)
		{
			Memory* memory = Memory::getInstance();
			list<Task*> expectedTaskList = *(memory->ramGetTaskList());
			Command_Add command(NULL);
			bool executionStatus;

			executionStatus = command.execute();

			Assert::AreEqual(false, executionStatus);
		}
	};

	TEST_CLASS(Command_DeleteTests)
	{
	public:

		TEST_METHOD(Command_DeleteTest_OutOfRange_LowValid)
		{
			Memory* memory = Memory::getInstance();
			Task* task = new Task();
			memory->ramAdd(task);
			memory->ramAdd(task);
			memory->ramAdd(task);
			memory->ramAdd(task);

			Command* command = new Command_Delete(1);
			bool executionStatus = command->execute();

			Assert::AreEqual(true, executionStatus);
		}

		TEST_METHOD(Command_DeleteTest_OutOfRange_HighValid)
		{
			Memory* memory = Memory::getInstance();
			Task* task = new Task();
			memory->ramAdd(task);
			memory->ramAdd(task);
			memory->ramAdd(task);
			memory->ramAdd(task);

			Command* command = new Command_Delete(4);
			bool executionStatus = command->execute();

			Assert::AreEqual(true, executionStatus);
		}

		TEST_METHOD(Command_DeleteTest_OutOfRange_LowInvalid1)
		{
			Memory* memory = Memory::getInstance();
			Task* task = new Task();
			memory->ramAdd(task);
			memory->ramAdd(task);
			memory->ramAdd(task);
			memory->ramAdd(task);

			Command* command = new Command_Delete(0);
			bool executionStatus = command->execute();

			Assert::AreEqual(false, executionStatus);
		}
		TEST_METHOD(Command_DeleteTest_OutOfRange_LowInvalid2)
		{
			Memory* memory = Memory::getInstance();
			Task* task = new Task();
			memory->ramAdd(task);
			memory->ramAdd(task);
			memory->ramAdd(task);
			memory->ramAdd(task);

			Command* command = new Command_Delete(-50);
			bool executionStatus = command->execute();

			Assert::AreEqual(false, executionStatus);
		}
		TEST_METHOD(Command_DeleteTest_OutOfRange_HighInvalid1)
		{
			Memory* memory = Memory::getInstance();
			Task* task = new Task();
			memory->ramAdd(task);
			memory->ramAdd(task);
			memory->ramAdd(task);
			memory->ramAdd(task);

			Command* command = new Command_Delete(5);
			bool executionStatus = command->execute();

			Assert::AreEqual(true, executionStatus);
		}
		TEST_METHOD(Command_DeleteTest_OutOfRange_HighInvalid2)
		{
			Memory* memory = Memory::getInstance();
			Task* task = new Task();
			memory->ramAdd(task);
			memory->ramAdd(task);
			memory->ramAdd(task);
			memory->ramAdd(task);

			Command* command = new Command_Delete(100000);
			bool executionStatus = command->execute();

			Assert::AreEqual(true, executionStatus);
		}
	};
}