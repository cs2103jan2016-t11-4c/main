//@@author A0130475L
#include "CommandFeedback.h"

const string CommandFeedback::DEFAULT_TEXT_FILE_NAME = "doMe.txt";
const string CommandFeedback::MESSAGE_VOID_STRING = "";
const string CommandFeedback::MESSAGE_TASK_INDEX = ", ";

const string CommandFeedback::MESSAGE_ADD = "Added \"%s\" into %s";
//const string CommandFeedback::MESSAGE_EMPTY = "Your text file \"%s\" is currently empty.";
const string CommandFeedback::MESSAGE_DELETE = "Deleted \"%s\" from %s";
const string CommandFeedback::MESSAGE_DELETE_MULTIPLE = "Deleted tasks \"%s\" from %s";
const string CommandFeedback::MESSAGE_EDIT = "Edited inputted task description to \"%s\"";
const string CommandFeedback::MESSAGE_EDIT_DONE = "Marked \"%s\" as DONE";
const string CommandFeedback::MESSAGE_CLEAR = "All tasks in view cleared.";
const string CommandFeedback::MESSAGE_SEARCH = "~Showing all results for \"%s\". Type \"exit\" to exit the search module~";
//const string CommandFeedback::MESSAGE_CLEAR_SEARCH = "All task with the search term \"%s\" is cleared.";
const string CommandFeedback::MESSAGE_CHANGE_FILE_DIRECTORY = "New save directory: %s";
const string CommandFeedback::MESSAGE_VIEW_TYPE = "Your current default view type is changed to (%d).";
const string CommandFeedback::MESSAGE_EXIT_SEARCH = "Exited search module.";
const string CommandFeedback::MESSAGE_EXIT_HELP = "Exited help module";
const string CommandFeedback::MESSAGE_REDO = "Redo - <%s>";

const string CommandFeedback::ERROR_INVALID_ADD = "Invalid (ADD) has been inputted.";
const string CommandFeedback::ERROR_INVALID_DELETE = "Invalid (DELETE) has been inputted.";
const string CommandFeedback::ERROR_INVALID_COMMAND_FORMAT = "Invalid command format has been inputted.";
const string CommandFeedback::ERROR_INVALID_COMMAND = "Invalid command has been inputted.";
const string CommandFeedback::ERROR_INVALID_VIEWTYPE = "Invalid (Viewtype) has been inputted.";
const string CommandFeedback::ERROR_INVALID_EDIT = "Invalid (EDIT) of task description.";
const string CommandFeedback::ERROR_INVALID_UNDO = "Invalid (UNDO) of previous command.";
const string CommandFeedback::ERROR_INVALID_REDO = "Invalid (REDO) of command.";
const string CommandFeedback::ERROR_INVALID_SAVE_FILE_DIRECTORY = "Invalid file directory.";


const string CommandFeedback::MESSAGE_UNDO_COMMAND = "Undo previous command.";
const string CommandFeedback::MESSAGE_UNDO_ADD = "Undo (ADD) of \"%s\"";
const string CommandFeedback::MESSAGE_UNDO_DELETE = "Undo (DELETE) of \"%s\"";
const string CommandFeedback::MESSAGE_UNDO_EDIT = "Undo (EDIT) of \"%s\"";
const string CommandFeedback::MESSAGE_UNDO_CLEAR = "Undo (CLEAR)";
const string CommandFeedback::MESSAGE_UNDO_VIEW_TYPE = "Undo (Viewtype) change of \"%d\"";
const string CommandFeedback::MESSAGE_UNDO_CHANGE_DIRECTORY = "Undo (Change Directory) of \"%s\"";

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
		taskListType = new ViewType();
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
			return getNotificationSearchTerm(undoCommandMessage, commandOutcome, viewType);
			//return "No undo exit";
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
		return validNotificationEdit(executionMessage->getTask(), viewType);
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

string CommandFeedback::validNotificationEdit(Task* task, int viewType) {
	string taskString;
	taskString = getTaskString(task,viewType);
	if(task->getDoneStatus() == true) {
		sprintf_s(buffer, MESSAGE_EDIT_DONE.c_str(),taskString.c_str());
	} else {
		sprintf_s(buffer, MESSAGE_EDIT.c_str(),taskString.c_str());
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
	sprintf_s(buffer, MESSAGE_CHANGE_FILE_DIRECTORY.c_str(), newDirectory.c_str());
	return buffer;
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
	taskString = getTaskString(executionMessage->getTask(), viewType);
	sprintf_s(buffer, MESSAGE_UNDO_EDIT.c_str(),taskString.c_str());
	return buffer;
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