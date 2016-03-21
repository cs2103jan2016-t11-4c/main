#include "UserInterface.h"

int main() {
	UserInterface doMeUI = UserInterface();

	doMeUI.setEnvironment();
	doMeUI.executeCommandUntilExit();

	return 0;
}