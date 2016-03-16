#pragma once
#include <list>
#include "RAM.h"
#include "Settings.h"
#include "Storage.h"
#include "Task.h"

class Memory {
public:
    Memory(void);
    ~Memory(void);

	static Memory* getInstance();
	
	//function calling Settings class
    bool loadSettings(); //complete
    void saveSettings(); //complete
    bool changeViewType(int viewType); //complete
    bool changeSaveDirectory(string saveDirectory);//complete
    string getTextFileName();//complete
    int getViewType();//complete
    string getSaveDirectory();//complete
    
    //functions calling Storage class
	bool getExistingData(); //complete 
    bool saveUpdatedData();//complete

	//functions calling RAM class
	void ramAddToRawTaskHeap(Task task);
	void ramAdd(Task* task);
	void ramDel(Task* task);
	Task* ramDel(int index);
	void ramClear();
	void ramInsert(list<Task*>& oldTaskList);
	int ramGetSize();
	Task* ramGetTask(int index);
	bool ramSearch(string searchTerm);
	string ramUnsearch();
	vector<string> ramGetVector();
	void ramLoadVector(vector<string>& existingData);
		
    list<Task*>* getTaskList();//complete

private:
    list<Task*>* _taskList;
    Settings* _settings;
    Storage* _storage;
	RAM* _ram;
	Memory* _instance;

    void vectorToTaskList(vector<string>& existingData);//complete
    vector<string> taskListToVector();//complete
    int stringToInteger(string text);//complete
    string integerToString(int integer);//complete

    static const string MESSAGE_VOID_STRING;
    static const string DEFAULT_TEXT_FILE_NAME;
    static const string LIST_DIVIDER;

};

