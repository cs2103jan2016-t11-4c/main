//@@author A0130475L
#pragma once
#include <string>
#include <vector>

using namespace std;

class HelpPrompt {
private:
    static HelpPrompt* _instance;
    vector<vector<string>*>* _helpList;

    HelpPrompt(void);
    vector<string>* createPrompt(const string messagePrompt[], int size);
    void createHelpList();

    static const string HelpPrompt::MESSAGE_HELP_TIPS_ADD[];
    static const string HelpPrompt::MESSAGE_HELP_TIPS_DEL[];
public:
    static HelpPrompt* getInstance();
    vector<vector<string>*>* getHelpList();
    void startHelpEngine();
    ~HelpPrompt(void);
};

