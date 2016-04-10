//@@author A0130475L
#include "Exception_CommandScroll.h"

const string Exception_CommandScroll::SCROLL_MESSAGES = "Press \"Up/Down/PgUp/PgDw\" to move page up and down. Press any other key to exit";

Exception_CommandScroll::Exception_CommandScroll(void) {
}

Exception_CommandScroll::~Exception_CommandScroll(void) {
}

string Exception_CommandScroll::getString() {
    return SCROLL_MESSAGES;
}
