//@@author A0130475L
#include "Command_Feedback.h"

const string Command_Feedback::DEFAULT_TEXT_FILE_NAME = "doMe.txt";
const string Command_Feedback::MESSAGE_VOID_STRING = "";

const string Command_Feedback::MESSAGE_ADD = "Added \"%s\" into %s";
//const string Command_Feedback::MESSAGE_EMPTY = "Your text file \"%s\" is currently empty.";
const string Command_Feedback::MESSAGE_DELETE = "Deleted \"%s\" from %s";
const string Command_Feedback::MESSAGE_EDIT = "Edited inputted task description to \"%s\"";
const string Command_Feedback::MESSAGE_CLEAR = "All contents cleared from %s";
const string Command_Feedback::MESSAGE_SEARCH = "~Showing all results for \"%s\". Type \"exit\" to exit the search module~";
//const string Command_Feedback::MESSAGE_CLEAR_SEARCH = "All task with the search term \"%s\" is cleared.";
const string Command_Feedback::MESSAGE_CHANGE_FILE_DIRECTORY = "New save directory: %s";
const string Command_Feedback::MESSAGE_VIEW_TYPE = "Your current default view type is changed to (%d).";
const string Command_Feedback::MESSAGE_EXIT_SEARCH = "Exited search module.";
const string Command_Feedback::MESSAGE_HELP = "Showing available commands and how to use them.";

const string Command_Feedback::ERROR_INVALID_ADD = "Invalid (ADD) has been inputted.";
const string Command_Feedback::ERROR_INVALID_DELETE = "Invalid (DELETE) has been inputted.";
const string Command_Feedback::ERROR_INVALID_COMMAND_FORMAT = "Invalid command format has been inputted.";
const string Command_Feedback::ERROR_INVALID_COMMAND = "Invalid command has been inputted.";
const string Command_Feedback::ERROR_INVALID_VIEWTYPE = "Invalid (Viewtype) has been inputted.";
const string Command_Feedback::ERROR_INVALID_EDIT = "Invalid (EDIT) of task description.";
const string Command_Feedback::ERROR_INVALID_UNDO = "Unable to undo previous command.";
const string Command_Feedback::ERROR_INVALID_SAVE_FILE_DIRECTORY = "Invalid inputted file directory.";

const string Command_Feedback::MESSAGE_UNDO_COMMAND = "Undo previous command.";
const string Command_Feedback::MESSAGE_UNDO_ADD = "Undo (ADD) of \"%s\"";
const string Command_Feedback::MESSAGE_UNDO_DELETE = "Undo (DELETE) of \"%s\"";
const string Command_Feedback::MESSAGE_UNDO_EDIT = "Undo (EDIT) of \"%s\"";
const string Command_Feedback::MESSAGE_UNDO_CLEAR = "Undo (CLEAR)";
const string Command_Feedback::MESSAGE_UNDO_VIEW_TYPE = "Undo (Viewtype) change of \"%d\"";
const string Command_Feedback::MESSAGE_UNDO_CHANGE_DIRECTORY = "Undo (Change Directory) of \"%s\"";

Command_Feedback* Command_Feedback::_instance = 0;

Command_Feedback* Command_Feedback::getInstance() {
    if (_instance == 0) {
        _instance = new Command_Feedback;
    }
    return _instance;
}

Command_Feedback::Command_Feedback(void) {
}

Command_Feedback::~Command_Feedback(void) {
}

/****************************************************************/

string Command_Feedback::getTaskString(Task* task, int viewType) {
    ViewType* taskListType;

    switch(viewType) {
    case 1:
        taskListType = new ViewType1();
        break;
    case 2:
        taskListType = new ViewType2();
        break;
    default:
        taskListType = new ViewType();
        break;
    }

    return taskListType->getTaskString(task);
}

string Command_Feedback::getCommandFeedback(Command* executionMessage, CommandOutcome commandOutcome, int viewType) {
    CommandType commandType = executionMessage->getCommandType();

    switch(commandType) {
    case ADD:
        return getNotificationAdd(executionMessage, commandOutcome, viewType);
        break;
    case DISPLAY:
        //return "no display UI";
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
        //return "auto sort?";
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
        //showToUser("Do I even need a exiting message? Nope");
        break;
    case HELP:
        return getNotificationHelpPrompt(executionMessage, commandOutcome, viewType);
        break;
    case INVALID:
        return getNotificationInvalidCommand(executionMessage, commandOutcome, viewType);
        break;
    default:
        break;
    }
    return MESSAGE_VOID_STRING;
}

/****************************************************************/

string Command_Feedback::getNotificationUndo(Command* executionMessage, CommandOutcome commandOutcome, int viewType) {
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
            //return "no display UI";
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
            //return "Unable to undo a undo";
            break;
        case SORT:
            assert(0);
            //return "auto sort?";
            break;
        case SEARCH:
            //return "Can you even undo a search?";
            return validNotificationExitSearch();
            break;
        case ENDSEARCH:
            //assert(0);
            return getNotificationSearchTerm(undoCommandMessage, commandOutcome, viewType);
            return "No undo exit";
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
            assert(0);
            //return "Taken care of";
            break;
        }
        return MESSAGE_UNDO_COMMAND;
        break;
    case INVALID_MESSAGE:
        return invalidNotificationUndo();
        break;
    }
}

string Command_Feedback::getNotificationRedo(Command* executionMessage, CommandOutcome commandOutcome, int viewType) {
    return getCommandFeedback(executionMessage, commandOutcome, viewType);
}

string Command_Feedback::getNotificationAdd(Command* executionMessage, CommandOutcome commandOutcome, int viewType) {
    switch(commandOutcome) {
    case VALID_MESSAGE:
        return validNotificationAdd(executionMessage->getTask(), viewType, DEFAULT_TEXT_FILE_NAME);
        break;
    case INVALID_MESSAGE:
        return invalidNotificationAdd();
        break;
    }

}

string Command_Feedback::getNotificationDelete(Command* executionMessage, CommandOutcome commandOutcome, int viewType) {
    switch(commandOutcome) {
    case VALID_MESSAGE:
        return validNotificationDelete(executionMessage->getTask(), viewType, DEFAULT_TEXT_FILE_NAME);
        break;
    case INVALID_MESSAGE:
        return invalidNotificationDelete();
        break;
    }
}

string Command_Feedback::getNotificationEdit(Command* executionMessage, CommandOutcome commandOutcome, int viewType) {
    switch(commandOutcome) {
    case VALID_MESSAGE:
        return validNotificationEdit(executionMessage->getTask(), viewType);
        break;
    case INVALID_MESSAGE:
        return invalidNotificationEdit();
        break;
    }
}

string Command_Feedback::getNotificationClear(Command* executionMessage, CommandOutcome commandOutcome, int viewType) {
    switch(commandOutcome) {
    case VALID_MESSAGE:
        return validNotificationClear(DEFAULT_TEXT_FILE_NAME);
        break;
    case INVALID_MESSAGE:
        return ERROR_INVALID_COMMAND;
        break;
    }
}

string Command_Feedback::getNotificationSearchTerm(Command* executionMessage, CommandOutcome commandOutcome, int viewType) {
    string searchTerm;
    searchTerm = executionMessage->getSearchTerm();
    return validNotificationSearchTerm(searchTerm);
}

string Command_Feedback::getNotificationEndSearch(Command* executionMessage, CommandOutcome commandOutcome, int viewType) {
    switch(commandOutcome) {
    case VALID_MESSAGE:
        return validNotificationExitSearch();
        break;
    case INVALID_MESSAGE:
        return ERROR_INVALID_COMMAND;
        break;
    }
}

string Command_Feedback::getNotificationViewType(Command* executionMessage, CommandOutcome commandOutcome, int viewType) {
    switch(commandOutcome) {
    case VALID_MESSAGE:
        return validNotificationViewType(executionMessage->getViewType());
        break;
    case INVALID_MESSAGE:
        return invalidNotificationViewtype();
        break;
    }
}

string Command_Feedback::getNotificationChangeSaveFileDirectory(Command* executionMessage, CommandOutcome commandOutcome, int viewType) {
    switch(commandOutcome) {
    case VALID_MESSAGE:
        return validNotificationChangeSaveFileDirectory(executionMessage->getSaveDirectory());
        break;
    case INVALID_MESSAGE:
        return invalidNotificationSaveFileDirectory();
        break;
    }
}

string Command_Feedback::getNotificationHelpPrompt(Command* executionMessage, CommandOutcome commandOutcome, int viewType) {
        return validNotificationHelpPrompt();
}

string Command_Feedback::getNotificationInvalidCommand(Command* executionMessage, CommandOutcome commandOutcome, int viewType) {
    return invalidNotificationCommand();
}

/****************************************************************/

string Command_Feedback::validNotificationAdd(Task* task, int viewType, string textFileName) {
    string taskString;
    taskString = getTaskString(task,viewType);
    sprintf_s(buffer, MESSAGE_ADD.c_str(),taskString.c_str(), textFileName.c_str());
    return buffer;
}

string Command_Feedback::validNotificationDelete(Task* task, int viewType, string textFileName) {
    string taskString;
    taskString = getTaskString(task,viewType);
    sprintf_s(buffer, MESSAGE_DELETE.c_str(),taskString.c_str(), textFileName.c_str());
    return buffer;
}

string Command_Feedback::validNotificationEdit(Task* task, int viewType) {
    string taskString;
    taskString = getTaskString(task,viewType);
    sprintf_s(buffer, MESSAGE_EDIT.c_str(),taskString.c_str());
    return buffer;
}

string Command_Feedback::validNotificationClear(string textFileName) {
    sprintf_s(buffer, MESSAGE_CLEAR.c_str(), textFileName.c_str());
    return buffer;
}

string Command_Feedback::validNotificationSearchTerm(string searchTerm) {
    sprintf_s(buffer, MESSAGE_SEARCH.c_str(), searchTerm.c_str());
    return buffer;
}

string Command_Feedback::validNotificationExitSearch() {
    sprintf_s(buffer, MESSAGE_EXIT_SEARCH.c_str());
    return buffer;
}

string Command_Feedback::validNotificationViewType(int newViewType) {
    sprintf_s(buffer, MESSAGE_VIEW_TYPE.c_str(), newViewType);
    return buffer;
}

string Command_Feedback::validNotificationChangeSaveFileDirectory(string newDirectory) {
    sprintf_s(buffer, MESSAGE_CHANGE_FILE_DIRECTORY.c_str(), newDirectory.c_str());
    return buffer;
}

string Command_Feedback::validNotificationHelpPrompt() {
    return MESSAGE_HELP;
}

/****************************************************************/

string Command_Feedback::invalidNotificationAdd() {
    return ERROR_INVALID_ADD;
}

string Command_Feedback::invalidNotificationDelete() {
    return ERROR_INVALID_DELETE;
}

string Command_Feedback::invalidNotificationEdit() {
    return ERROR_INVALID_EDIT;
}

string Command_Feedback::invalidNotificationViewtype() {
    return ERROR_INVALID_VIEWTYPE;
}

string Command_Feedback::invalidNotificationSaveFileDirectory() {
    return ERROR_INVALID_SAVE_FILE_DIRECTORY;
}

string Command_Feedback::invalidNotificationCommand() {
    return ERROR_INVALID_COMMAND;
}

string Command_Feedback::invalidNotificationUndo() {
    return ERROR_INVALID_UNDO;
}

/****************************************************************/

string Command_Feedback::undoNotificationAdd(Command* executionMessage, int viewType) {
    string taskString;
    taskString = getTaskString(executionMessage->getTask(), viewType);
    sprintf_s(buffer, MESSAGE_UNDO_ADD.c_str(),taskString.c_str());
    return buffer;
}

string Command_Feedback::undoNotificationDel(Command* executionMessage, int viewType) {
    string taskString;
    taskString = getTaskString(executionMessage->getTask(), viewType);
    sprintf_s(buffer, MESSAGE_UNDO_DELETE.c_str(),taskString.c_str());
    return buffer;
}

string Command_Feedback::undoNotificationEdit(Command* executionMessage, int viewType) {
    string taskString;
    taskString = getTaskString(executionMessage->getTask(), viewType);
    sprintf_s(buffer, MESSAGE_UNDO_EDIT.c_str(),taskString.c_str());
    return buffer;
}

string Command_Feedback::undoNotificationClear(Command* executionMessage, int viewType) {
    return MESSAGE_UNDO_CLEAR;
}

string Command_Feedback::undoNotificationViewType(Command* executionMessage, int viewType) {
    sprintf_s(buffer, MESSAGE_UNDO_VIEW_TYPE.c_str(),executionMessage->getViewType());
    return buffer;
}

string Command_Feedback::undoNotificationChangDirectory(Command* executionMessage, int viewType) {
    sprintf_s(buffer, MESSAGE_UNDO_CHANGE_DIRECTORY.c_str(),executionMessage->getSaveDirectory());
    return buffer;
}

/****************************************************************/
