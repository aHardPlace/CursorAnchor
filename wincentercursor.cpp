#include <windows.h>

int main() {
	const int highBit = (1 << 16);
	SHORT curKeyState;
	while (true) {
		curKeyState = GetAsyncKeyState(VK_F3);
		if (highBit & curKeyState) {
			SetCursorPos(GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN) / 2);
		}

		Sleep(40);
	}

	return 0;
}
