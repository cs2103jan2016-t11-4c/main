#include "Logic.h"

int main() {
	Logic doMeLogic = Logic();

	doMeLogic.setEnvironment();
	doMeLogic.displayWelcomeMessage();
	doMeLogic.executeCommandsUntilExitCommand();

	return 0;
}