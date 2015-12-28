/*	Cursor Anchor
 *
 * 	Moves the cursor to an anchor point when a key is hit.
 *	Default is the center of the first screen.
 *
 *	Author: github.com/aHardPlace
 *	Version: 1.0
 *
 *  Title art generated at network-science.de/ascii
*/	

#include <cstdio>
#include <windows.h>

int main() {
	SetConsoleTitle("Cursor Anchor");
	puts("  ______  __    __ .______        _______.  ______  .______           ");
	puts(" /      ||  |  |  ||   _  \\      /       | /  __  \\ |   _  \\       ");
	puts("|  ,----'|  |  |  ||  |_)  |    |   (----`|  |  |  ||  |_)  |         ");
	puts("|  |     |  |  |  ||      /      \\   \\    |  |  |  ||      /        ");
	puts("|  `----.|  `--'  ||  |\\  \\-------)   |   |  `--'  ||  |\\  \\----. ");
	puts(" \\______| \\______/ |__| `.___________/     \\______/ |__| `._____|  ");
	puts("     ___      .__   __.  ______  __    __   ______  .______           ");
	puts("    /   \\     |  \\ |  | /      ||  |  |  | /  __  \\ |   _  \\      ");
	puts("   /  _  \\    |   \\|  ||  ,----'|  |__|  ||  |  |  ||  |_)  |       ");
	puts("  /  /_\\  \\   |  . `  ||  |     |   __   ||  |  |  ||      /        ");
	puts(" /  _____  \\  |  |\\   ||  `----.|  |  |  ||  `--'  ||  |\\  \\----. ");
	puts("/__/     \\__\\ |__| \\__| \\______||__|  |__| \\______/ |__| `._____|");
	puts("Listening...");

	POINT mouseAnchor = { // center of first screen by default
		GetSystemMetrics(SM_CXSCREEN) / 2, 
		GetSystemMetrics(SM_CYSCREEN) / 2
	};
	while (true) {
		if (GetAsyncKeyState(VK_F2) & 1) { // checking lowest bit stops spam unless button is held
			GetCursorPos(&mouseAnchor);
			printf("New anchor: %li, %li\n", mouseAnchor.x, mouseAnchor.y);
		}
		if (GetAsyncKeyState(VK_F3)) {
			SetCursorPos(mouseAnchor.x, mouseAnchor.y);
		}

		Sleep(40); // sensibly arbitrary milliseconds
	}

	return 0;
}