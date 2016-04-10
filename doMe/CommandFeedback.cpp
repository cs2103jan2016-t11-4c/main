//@@author A0130475L
#include "CommandFeedback.h"

const string CommandFeedback::DEFAULT_TEXT_FILE_NAME = "doMe.txt";
const string CommandFeedback::MESSAGE_VOID_STRING = "";
const string CommandFeedback::MESSAGE_TASK_INDEX = ", ";

const string CommandFeedback::MESSAGE_ADD = "Added \"%s\" into %s";
const string CommandFeedback::MESSAGE_DELETE = "Deleted \"%s\" from %s";
const string CommandFeedback::MESSAGE_DELETE_MULTIPLE = "Deleted tasks \"%s\" from %s";
const string CommandFeedback::MESSAGE_EDIT = "Editted task to \"%s\".";
const string CommandFeedback::MESSAGE_EDIT_DONE = "Marked \"%s\" as DONE.";
const string CommandFeedback::MESSAGE_EDIT_UNDONE = "Marked \"%s\" as UNDONE.";
const string CommandFeedback::MESSAGE_CLEAR = "All tasks in view cleared.";
const string CommandFeedback::MESSAGE_SEARCH = "~Showing all results for \"%s\". Type \"exit\" to exit the search module~";
const string CommandFeedback::MESSAGE_CHANGE_FILE_DIRECTORY = "Save Directory changed to %s";
const string CommandFeedback::MESSAGE_DEFAULT_FILE_DIRECTORY = "Save directory changed to <Default Directory>";
const string CommandFeedback::MESSAGE_VIEW_TYPE = "Viewtype has been changed to (%d).";
const string CommandFeedback::MESSAGE_EXIT_SEARCH = "Exited SEARCH module.";
const string CommandFeedback::MESSAGE_EXIT_HELP = "Exited HELP module.";
const string CommandFeedback::MESSAGE_REDO = "Redo <%s>.";

const string CommandFeedback::ERROR_INVALID_ADD = "Invalid (ADD) command been inputted.";
const string CommandFeedback::ERROR_INVALID_DELETE = "Invalid (DELETE) command has been entered.";
const string CommandFeedback::ERROR_INVALID_COMMAND_FORMAT = "Invalid command format has been entered.";
const string CommandFeedback::ERROR_INVALID_COMMAND = "Invalid command has been entered.";
const string CommandFeedback::ERROR_INVALID_VIEWTYPE = "Invalid (Viewtype) has been entered.";
const string CommandFeedback::ERROR_INVALID_EDIT = "Invalid (EDIT) command has been entered.";
const string CommandFeedback::ERROR_INVALID_UNDO = "No UNDOs found.";
const string CommandFeedback::ERROR_INVALID_REDO = "No REDOs found.";
const string CommandFeedback::ERROR_INVALID_SAVE_FILE_DIRECTORY = "Invalid directory has been entered.";


const string CommandFeedback::MESSAGE_UNDO_COMMAND = "Previous command undone.";
const string CommandFeedback::MESSAGE_UNDO_ADD = "Undid (ADD) of \"%s\".";
const string CommandFeedback::MESSAGE_UNDO_DELETE = "Undid (DELETE) of \"%s\".";
const string CommandFeedback::MESSAGE_UNDO_EDIT = "Undid (EDIT) of \"%s\".";
const string CommandFeedback::MESSAGE_UNDO_EDIT_DONE = "Undid (DONE) of \"%s\".";
const string CommandFeedback::MESSAGE_UNDO_EDIT_UNDONE = "Undid (UNDONE) of \"%s\".";
const string CommandFeedback::MESSAGE_UNDO_CLEAR = "Undid (CLEAR).";
const string CommandFeedback::MESSAGE_UNDO_VIEW_TYPE = "Undid (Viewtype) change of \"%d\".";
const string CommandFeedback::MESSAGE_UNDO_CHANGE_DIRECTORY = "Undid (Change Directory) of \"%s\".";

CommandFeedback* CommandFeedback::_instance = 0;

CommandFeedback* CommandFeedback::getInstance() {
    if (_instance == 0) {
        _instance = new CommandFeedback;
    }
    return _instance;
}

CommandFeedback::CommandFeedback(void) {
}

CommandFeedback::~CommandFeedback(void) {
}

/****************************************************************/

string CommandFeedback::getTaskString(Task* task, int viewType) {
    ViewType* taskListType;

    switch(viewType) {
    case 1:
        taskListType = new ViewType1();
        break;
    case 2:
        taskListType = new ViewType2();
        break;
    case 3:
        taskListType = new ViewType3();
        break;
    default:
        taskListType = new ViewType0();
        break;
    }

    return taskListType->getTaskString(task);
}

string CommandFeedback::getCommandFeedback(Command* executionMessage, CommandOutcome commandOutcome, int viewType) {
    CommandType commandType = executionMessage->getCommandType();

    switch(commandType) {
    case ADD:
        return getNotificationAdd(executionMessage, commandOutcome, viewType);
        break;
    case DISPLAY:
        break;
    case DEL:
        return getNotificationDelete(executionMessage, commandOutcome, viewType);
        break;
    case EDIT:
        return getNotificationEdit(executionMessage, commandOutcome, viewType);
        break;
    case CLEAR:
        return getNotificationClear(executionMessage, commandOutcome, viewType);
        break;
    case UNDO:
        return getNotificationUndo(executionMessage, commandOutcome, viewType);
        break;
    case REDO:
        return getNotificationRedo(executionMessage, commandOutcome, viewType);
        break;
    case SORT:
        break;
    case SEARCH:
        return getNotificationSearchTerm(executionMessage, commandOutcome, viewType);
        break;
    case ENDSEARCH:
        return getNotificationEndSearch(executionMessage, commandOutcome, viewType);
        break;
    case VIEWTYPE:
        return getNotificationViewType(executionMessage, commandOutcome, viewType);
        break;
    case SAVEDIRECTORY:
        return getNotificationChangeSaveFileDirectory(executionMessage, commandOutcome, viewType);
        break;
    case EXIT:
        break;
    case HELP:
        return getNotificationHelpPrompt(executionMessage, commandOutcome, viewType);
        break;
    case INVALID:
        return getNotificationInvalidCommand(executionMessage, commandOutcome, viewType);
        break;
    case SCROLL:
        throw Exception_CommandScroll();
        break;        
    default:
        break;
    }
    return MESSAGE_VOID_STRING;
}

/****************************************************************/

string CommandFeedback::getNotificationUndo(Command* executionMessage, CommandOutcome commandOutcome, int viewType) {
    Command* undoCommandMessage;
    CommandType commandType;

    switch(commandOutcome) {
    case VALID_MESSAGE:
        undoCommandMessage = executionMessage->getUndoneCommand();
        commandType = undoCommandMessage->getCommandType();
        switch(commandType) {
        case ADD:
            return undoNotificationAdd(undoCommandMessage, viewType);
            break;
        case DISPLAY:
            assert(0);
            break;
        case DEL:
            return undoNotificationDel(undoCommandMessage, viewType);
            break;
        case EDIT:
            return undoNotificationEdit(undoCommandMessage, viewType);
            break;
        case CLEAR:
            return undoNotificationClear(undoCommandMessage, viewType);
            break;
        case UNDO:
            assert(0);
            break;
        case SORT:
            assert(0);
            break;
        case SEARCH:
            return validNotificationExitSearch();
            break;
        case ENDSEARCH:
            return getNotificationSearchTerm(undoCommandMessage, commandOutcome, viewType);
            break;
        case VIEWTYPE:
            return undoNotificationViewType(undoCommandMessage, viewType);
            break;
        case SAVEDIRECTORY:
            return undoNotificationChangDirectory(undoCommandMessage, viewType);
            break;
        case EXIT:
            assert(0);
            break;
        case INVALID:
            return invalidNotificationUndo();
            break;
        }
    case INVALID_MESSAGE:
        return invalidNotificationUndo();
        break;
    }
    return MESSAGE_UNDO_COMMAND;
}

string CommandFeedback::getNotificationRedo(Command* executionMessage, CommandOutcome commandOutcome, int viewType) {
    string redoString;

    switch(commandOutcome) {
    case VALID_MESSAGE:
        redoString = getCommandFeedback(executionMessage->getRedoneCommand(), commandOutcome, viewType);
        return validNotificationRedo(redoString);
        break;
    case INVALID_MESSAGE:
        return invalidNotificationRedo();
        break;
    }
    return ERROR_INVALID_COMMAND;
}

string CommandFeedback::getNotificationAdd(Command* executionMessage, CommandOutcome commandOutcome, int viewType) {
    switch(commandOutcome) {
    case VALID_MESSAGE:
        return validNotificationAdd(executionMessage->getTask(), viewType, DEFAULT_TEXT_FILE_NAME);
        break;
    case INVALID_MESSAGE:
        return invalidNotificationAdd();
        break;
    }
    return ERROR_INVALID_COMMAND;
}

string CommandFeedback::getNotificationDelete(Command* executionMessage, CommandOutcome commandOutcome, int viewType) {
    vector<int>* deleteList;
    switch(commandOutcome) {
    case VALID_MESSAGE:
        deleteList = executionMessage->getDeleteList();
        if(deleteList->size() > 1) {
            return validNotificationDeleteMultiple(deleteList, viewType, DEFAULT_TEXT_FILE_NAME);
        } else {
            return validNotificationDelete(executionMessage->getTask(), viewType, DEFAULT_TEXT_FILE_NAME);
        }
        break;
    case INVALID_MESSAGE:
        return invalidNotificationDelete();
        break;
    }
    return ERROR_INVALID_COMMAND;
}

string CommandFeedback::getNotificationEdit(Command* executionMessage, CommandOutcome commandOutcome, int viewType) {
    switch(commandOutcome) {
    case VALID_MESSAGE:
        return validNotificationEdit(executionMessage->getTask(), viewType, executionMessage->getDoneStatus());
        break;
    case INVALID_MESSAGE:
        return invalidNotificationEdit();
        break;
    }
    return ERROR_INVALID_COMMAND;
}

string CommandFeedback::getNotificationClear(Command* executionMessage, CommandOutcome commandOutcome, int viewType) {
    switch(commandOutcome) {
    case VALID_MESSAGE:
        return validNotificationClear(DEFAULT_TEXT_FILE_NAME);
        break;
    case INVALID_MESSAGE:
        return ERROR_INVALID_COMMAND;
        break;
    }
    return ERROR_INVALID_COMMAND;
}

string CommandFeedback::getNotificationSearchTerm(Command* executionMessage, CommandOutcome commandOutcome, int viewType) {
    string searchTerm;
    searchTerm = executionMessage->getSearchTerm();
    return validNotificationSearchTerm(searchTerm);
}

string CommandFeedback::getNotificationEndSearch(Command* executionMessage, CommandOutcome commandOutcome, int viewType) {
    switch(commandOutcome) {
    case VALID_MESSAGE:
        return validNotificationExitSearch();
        break;
    case INVALID_MESSAGE:
        return ERROR_INVALID_COMMAND;
        break;
    }
    return ERROR_INVALID_COMMAND;
}

string CommandFeedback::getNotificationViewType(Command* executionMessage, CommandOutcome commandOutcome, int viewType) {
    switch(commandOutcome) {
    case VALID_MESSAGE:
        return validNotificationViewType(executionMessage->getViewType());
        break;
    case INVALID_MESSAGE:
        return invalidNotificationViewtype();
        break;
    }
    return ERROR_INVALID_COMMAND;
}

string CommandFeedback::getNotificationChangeSaveFileDirectory(Command* executionMessage, CommandOutcome commandOutcome, int viewType) {
    switch(commandOutcome) {
    case VALID_MESSAGE:
        return validNotificationChangeSaveFileDirectory(executionMessage->getSaveDirectory());
        break;
    case INVALID_MESSAGE:
        return invalidNotificationSaveFileDirectory();
        break;
    }
    return ERROR_INVALID_COMMAND;
}

string CommandFeedback::getNotificationHelpPrompt(Command* executionMessage, CommandOutcome commandOutcome, int viewType) {
    return validNotificationHelpPrompt();
}

string CommandFeedback::getNotificationInvalidCommand(Command* executionMessage, CommandOutcome commandOutcome, int viewType) {
    return invalidNotificationCommand();
}

/****************************************************************/

string CommandFeedback::validNotificationAdd(Task* task, int viewType, string textFileName) {
    string taskString;
    taskString = getTaskString(task,viewType);
    sprintf_s(buffer, MESSAGE_ADD.c_str(),taskString.c_str(), textFileName.c_str());
    return buffer;
}

string CommandFeedback::validNotificationDelete(Task* task, int viewType, string textFileName) {
    string taskString;
    taskString = getTaskString(task,viewType);
    sprintf_s(buffer, MESSAGE_DELETE.c_str(),taskString.c_str(), textFileName.c_str());
    return buffer;
}

string CommandFeedback::validNotificationDeleteMultiple(vector<int>* deleteIndex, int viewType, string textFileName) {
    string taskString;
    vector<int>::iterator intIter = deleteIndex->begin();
    while(intIter != deleteIndex->end()) {
        taskString = taskString + taskIndexToString(*intIter);
        intIter++;
    }
    sprintf_s(buffer, MESSAGE_DELETE_MULTIPLE.c_str(), taskString.c_str(), textFileName.c_str());
    return buffer;
}

string CommandFeedback::validNotificationEdit(Task* task, int viewType, int doneStatus) {
    string taskString;
    taskString = getTaskString(task,viewType);
    if(doneStatus == 1) {
        sprintf_s(buffer, MESSAGE_EDIT_DONE.c_str(),taskString.c_str());
    } else {
        if(doneStatus == -1) {
            sprintf_s(buffer, MESSAGE_EDIT.c_str(),taskString.c_str());
        } else {
            sprintf_s(buffer, MESSAGE_EDIT_UNDONE.c_str(),taskString.c_str());
        }
    }
    return buffer;
}

string CommandFeedback::validNotificationClear(string textFileName) {
    return MESSAGE_CLEAR;
}

string CommandFeedback::validNotificationSearchTerm(string searchTerm) {
    sprintf_s(buffer, MESSAGE_SEARCH.c_str(), searchTerm.c_str());
    return buffer;
}

string CommandFeedback::validNotificationExitSearch() {
    sprintf_s(buffer, MESSAGE_EXIT_SEARCH.c_str());
    return buffer;
}

string CommandFeedback::validNotificationViewType(int newViewType) {
    sprintf_s(buffer, MESSAGE_VIEW_TYPE.c_str(), newViewType);
    return buffer;
}

string CommandFeedback::validNotificationChangeSaveFileDirectory(string newDirectory) {
    if(newDirectory.empty()) {
        return MESSAGE_DEFAULT_FILE_DIRECTORY;
    } else {
        sprintf_s(buffer, MESSAGE_CHANGE_FILE_DIRECTORY.c_str(), newDirectory.c_str());
        return buffer;
    }

}

string CommandFeedback::validNotificationHelpPrompt() {
    return MESSAGE_EXIT_HELP;
}

string CommandFeedback::validNotificationRedo(string redoString) {
    sprintf_s(buffer, MESSAGE_REDO.c_str(),redoString.c_str());
    return buffer;
}

/****************************************************************/

string CommandFeedback::invalidNotificationAdd() {
    return ERROR_INVALID_ADD;
}

string CommandFeedback::invalidNotificationDelete() {
    return ERROR_INVALID_DELETE;
}

string CommandFeedback::invalidNotificationEdit() {
    return ERROR_INVALID_EDIT;
}

string CommandFeedback::invalidNotificationViewtype() {
    return ERROR_INVALID_VIEWTYPE;
}

string CommandFeedback::invalidNotificationSaveFileDirectory() {
    return ERROR_INVALID_SAVE_FILE_DIRECTORY;
}

string CommandFeedback::invalidNotificationCommand() {
    return ERROR_INVALID_COMMAND;
}

string CommandFeedback::invalidNotificationUndo() {
    return ERROR_INVALID_UNDO;
}

string CommandFeedback::invalidNotificationRedo() {
    return ERROR_INVALID_REDO;
}

/****************************************************************/

string CommandFeedback::undoNotificationAdd(Command* executionMessage, int viewType) {
    string taskString;
    taskString = getTaskString(executionMessage->getTask(), viewType);
    sprintf_s(buffer, MESSAGE_UNDO_ADD.c_str(),taskString.c_str());
    return buffer;
}

string CommandFeedback::undoNotificationDel(Command* executionMessage, int viewType) {
    string taskString;
    taskString = getTaskString(executionMessage->getTask(), viewType);
    sprintf_s(buffer, MESSAGE_UNDO_DELETE.c_str(),taskString.c_str());
    return buffer;
}

string CommandFeedback::undoNotificationEdit(Command* executionMessage, int viewType) {
    string taskString;
    int doneStatus = executionMessage->getDoneStatus();
    switch(doneStatus) {
    case -1:
        taskString = getTaskString(executionMessage->getTask(), viewType);
        sprintf_s(buffer, MESSAGE_UNDO_EDIT.c_str(),taskString.c_str());
        return buffer;
        break;
    case 0:
        taskString = getTaskString(executionMessage->getTask(), viewType);
        sprintf_s(buffer, MESSAGE_UNDO_EDIT_UNDONE.c_str(),taskString.c_str());
        return buffer;
        break;
    case 1:
        taskString = getTaskString(executionMessage->getTask(), viewType);
        sprintf_s(buffer, MESSAGE_UNDO_EDIT_DONE.c_str(),taskString.c_str());
        return buffer;
        break;
    default:
        return MESSAGE_VOID_STRING;
    }

}

string CommandFeedback::undoNotificationClear(Command* executionMessage, int viewType) {
    return MESSAGE_UNDO_CLEAR;
}

string CommandFeedback::undoNotificationViewType(Command* executionMessage, int viewType) {
    sprintf_s(buffer, MESSAGE_UNDO_VIEW_TYPE.c_str(),executionMessage->getViewType());
    return buffer;
}

string CommandFeedback::undoNotificationChangDirectory(Command* executionMessage, int viewType) {
    sprintf_s(buffer, MESSAGE_UNDO_CHANGE_DIRECTORY.c_str(),executionMessage->getSaveDirectory());
    return buffer;
}

/****************************************************************/
string CommandFeedback::taskIndexToString(int index) {
    ostringstream oss;
    oss << index;  
    string indexString = oss.str();

    return indexString + MESSAGE_TASK_INDEX;
}