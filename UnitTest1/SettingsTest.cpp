#include "stdafx.h"
#include "CppUnitTest.h"
#include "TesterHeader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {		
	TEST_CLASS(SettingTest) {
public:

	TEST_METHOD(TextFileNameMakerTest) {
		Settings Settings;
		string input = "text";
		string actualTexFileName;
		string expectedTextFileName = "text.txt";

		actualTexFileName = Settings.createTextFileNameString(input);
		Settings.updateTextFileName(input);

		Assert::AreEqual(actualTexFileName, expectedTextFileName);
		Assert::AreEqual(Settings._textFileName, expectedTextFileName);
	}

	TEST_METHOD(ChangeDirectoryTest) {
		Settings Settings;
		string input = "C:/Users/PeiChangHong/Documents/NUS Modules 14 I 15/Semester 4/CS2103/Core";
		string actualTexFileName;
		string expectedTextFileName = "mytextfile.txt";
		string expectedDirectory = "C:/Users/PeiChangHong/Documents/NUS Modules 14 I 15/Semester 4/CS2103/Core/";

		Assert::AreEqual(true,Settings.checkValidityOfDirectory(input));

		string input2 = "C:/Users/PeiChangHong/Documents/NUS Modules 14 I 15/Semester 4/CS2103/Core/mytextfile.txt";
		Settings.changeDirectory(input2);
		Assert::AreEqual(Settings._textFileName , expectedTextFileName);
		Assert::AreEqual(Settings._saveDirectory , expectedDirectory);
	}

	TEST_METHOD(GetDirectoryTest) {
		Settings Settings;
		Settings._textFileName = "text.txt";
		string expectedDirectory = "text.txt";

		Assert::AreEqual(Settings.getDirectory(), expectedDirectory);
	}
	
	};
}