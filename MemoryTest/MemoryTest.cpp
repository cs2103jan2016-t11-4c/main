#include "stdafx.h"
#include "CppUnitTest.h"

#include "Storage.h"
#include "Storage.cpp"
#include "Exception_FileCannotOpen.h"
#include "Exception_FileCannotOpen.cpp"

#include <string>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace MemoryTest {		
    TEST_CLASS(StorageTest) {
public:

    TEST_METHOD(Storage_RetrieveTest) {
        Storage* storage = Storage::getInstance();
        int totalLines = 4;
        string readDirectory = "storagetestread.txt";
        vector<string> actualData = storage->retrieveData(readDirectory);

        string expectedData[] = {
            "This is a test.",
            "Line 2",
            "Line 3",
            "This is the final line."
        };

        Assert::AreEqual(totalLines, (int)actualData.size());

        for (int i = 0; i < totalLines; i++) {
            Assert::AreEqual(expectedData[i], actualData[i]);
        }
    }

    TEST_METHOD(Storage_SaveTest) {
        // RetrieveTest must pass for SaveTest to be valid. 
        Storage* storage = Storage::getInstance();
        int totalLines = 4;
        string writeDirectory = "storagetestwrite.txt";
        vector<string> actualData;

        string expectedData[] = {
            "This is a test.",
            "Line 2",
            "Line 3",
            "This is the final line."
        };
        vector<string> newData(expectedData, expectedData + sizeof(expectedData) / sizeof(string));

        storage->saveData(newData, writeDirectory);
        actualData = storage->retrieveData(writeDirectory);

        Assert::AreEqual(totalLines, (int)actualData.size());

        for (int i = 0; i < totalLines; i++) {
            Assert::AreEqual(expectedData[i], actualData[i]);
        }
    }
    };
}