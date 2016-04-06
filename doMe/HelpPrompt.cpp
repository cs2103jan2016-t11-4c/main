//@@author A0130475L
#include "HelpPrompt.h"
const string HelpPrompt::MESSAGE_HELP_TIPS_ADD[] = { 
"                         +-----------------------------------------------+",
"Adding a task            |              OPTIONAL PARAMETERS*             |",
"+----------+-------------+--------------------+--------------+-----------+",
"| MODIFIER | TASK NAME   | DATE               | TIME         | LOCATION  |",
"+----------+-------------+--------------------+--------------+-----------+",
"| <empty>  | Cycling     | 14/02/2016         | 1100         | @Florist  |",
"| add      | Buy flowers | 14/02/16           | 2359         | @the park |",
"| a        |             | 14/02              | 11am         |           |",
"|          |             | 14 Feb             | 1159pm       |           |",
"|          |             | 14 Feb to 16 Feb   | 1100 to 2359 |           |",
"|          |             | 14 Feb - 16 Feb    | 1100 - 2359  |           |",
"|          |             |                    |              |           |",
"|          |             | today              |              |           |",
"|          |             | tmr, tomorrow      |              |           |",
"|          |             | mon, tue...        |              |           |",
"|          |             | monday, tuesday... |              |           |",
"|          |             | next mon           |              |           |",
"|          |             | next tuesday       |              |           |",
"|          |             | mon to wed         |              |           |",
"|          |             | mon - wed          |              |           |",
"|          |             |                    |              |           |",
"+----------+-------------+--------------------+--------------+-----------+",
"*Optional parameters can be input in any order eg. \"cycling 7pm @park today\"."
"",
"",
"",
"",
};

const string HelpPrompt::MESSAGE_HELP_TIPS_DEL[] = { 
"           Deleting Task           +------------------------+",
"           & Task Parameters       |   OPTIONAL PARAMETERS  |",
"           +----------+------------+------+------+----------+",
"           | MODIFIER | TASK INDEX | DATE | TIME | LOCATION |",
"           +----------+------------+------+------+----------+",
"           | delete   | <empty>*   | date | time | location |",
"           | del      | 1          | d    | t    | l        |",
"           | d        | 12         |      |      |          |",
"           |          | 1-12       |      |      |          |",
"           |          | 1 - 12     |      |      |          |",
"           |          |            |      |      |          |",
"           |          |            |      |      |          |",
"           | clear    | <empty>**  | n/a  | n/a  | n/a      |",
"           |          | 1          |      |      |          |",
"           |          | 12         |      |      |          |",
"           |          | 1-12       |      |      |          |",
"           |          | 1 - 12     |      |      |          |",
"           |          |            |      |      |          |",
"           +----------+------------+------+------+----------+",
"           *Deleting <empty> index directs program to Last Added Task.",
"           **Clearing <empty> index clears all tasks in view.",
"",
"",
"                       press any key to continue",
"",
"           Deleting Task           +------------------------+",
"           & Task Parameters       |   OPTIONAL PARAMETERS  |",
"           +----------+------------+------+------+----------+",
"           | MODIFIER | TASK INDEX | DATE | TIME | LOCATION |",
"           +----------+------------+------+------+----------+",
"           | delete   | <empty>*   | date | time | location |",
"           | del      | 1          | d    | t    | l        |",
"           | d        | 12         |      |      |          |",
"           |          | 1-12       |      |      |          |",
"           |          | 1 - 12     |      |      |          |",
"           |          |            |      |      |          |",
"           |          |            |      |      |          |",
"           | clear    | <empty>**  | n/a  | n/a  | n/a      |",
"           |          | 1          |      |      |          |",
"           |          | 12         |      |      |          |",
"           |          | 1-12       |      |      |          |",
"           |          | 1 - 12     |      |      |          |",
"           |          |            |      |      |          |",
"           +----------+------------+------+------+----------+",
"           *Deleting <empty> index directs program to Last Added Task.",
"           **Clearing <empty> index clears all tasks in view.",
"",
"",
"                       press any key to continue",
"                Deleting Task           +------------------------+",
"                & Task Parameters       |   OPTIONAL PARAMETERS  |",
"                +----------+------------+------+------+----------+",
"                | MODIFIER | TASK INDEX | DATE | TIME | LOCATION |",
"                +----------+------------+------+------+----------+",
"                | delete   | <empty>*   | date | time | location |",
"                | del      | 1          | d    | t    | l        |",
"                | d        | 12         |      |      |          |",
"                |          | 1-12       |      |      |          |",
"                |          | 1 - 12     |      |      |          |",
"                |          |            |      |      |          |",
"                |          |            |      |      |          |",
"                | clear    | <empty>**  | n/a  | n/a  | n/a      |",
"                |          | 1          |      |      |          |",
"                |          | 12         |      |      |          |",
"                |          | 1-12       |      |      |          |",
"                |          | 1 - 12     |      |      |          |",
"                |          |            |      |      |          |",
"                +----------+------------+------+------+----------+",
"           *Deleting <empty> index directs program to Last Added Task.",
"           **Clearing <empty> index clears all tasks in view.",
"",
"",
"                       press any key to continue",

};

HelpPrompt* HelpPrompt::_instance = 0;

HelpPrompt* HelpPrompt::getInstance() {
	if (_instance == 0) {
		_instance = new HelpPrompt;
	}
	return _instance;	
}

HelpPrompt::HelpPrompt(void) {
    createHelpList();
}

HelpPrompt::~HelpPrompt(void) {
}

/****************************************************************/

void HelpPrompt::startHelpEngine() {
}

vector<string>* HelpPrompt::createPrompt(const string messagePrompt[], int size) {
    vector<string>* helpList;

    helpList = new vector<string>(messagePrompt, messagePrompt+size);

    return helpList;
}

void HelpPrompt::createHelpList() {
    size_t size;
    _helpList = new vector<vector<string>*>;

    size = (sizeof(MESSAGE_HELP_TIPS_ADD)/sizeof(*MESSAGE_HELP_TIPS_ADD));
    _helpList->push_back(createPrompt(MESSAGE_HELP_TIPS_ADD, size));

    size = (sizeof(MESSAGE_HELP_TIPS_DEL)/sizeof(*MESSAGE_HELP_TIPS_DEL));
    _helpList->push_back(createPrompt(MESSAGE_HELP_TIPS_DEL, size));

}

vector<vector<string>*>* HelpPrompt::getHelpList() {
    return _helpList;
}


