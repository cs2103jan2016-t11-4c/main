#pragma once
#include <list>
#include "Task.h"
#include "Settings.h"
#include "Storage.h"

class Memory {
public:
    Memory(void);
    ~Memory(void);

    bool loadSettings(); //complete
    void saveSettings(); //complete
    bool changeViewType(int viewType); //complete
    bool changeSaveDirectory(string saveDirectory);//complete
    bool getExistingData(); //complete
    void saveUpdatedData();//complete
    string getTextFileName();//complete
    int getViewType();//complete
    string getSaveDirectory();//complete
    list<Task*>* getTaskList();//complete

private:
    list<Task*>* _taskList;
    Settings* _settings;
    Storage* _storage;

    void vectorToTaskList(vector<string>& existingData);//complete
    vector<string> taskListToVector();//complete
    int stringToInteger(string text);//complete
    string integerToString(int integer);//complete

    static const string MESSAGE_VOID_STRING;
    static const string DEFAULT_TEXT_FILE_NAME;
    static const string LIST_DIVIDER;

};

