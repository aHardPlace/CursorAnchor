#include <windows.h>

int main() {
	const int centerScreenX = GetSystemMetrics(SM_CXSCREEN) / 2;
	const int centerScreenY = GetSystemMetrics(SM_CYSCREEN) / 2;
	const int highBit = (1 << 16);
	while (true) {
		if (highBit & GetAsyncKeyState(VK_F3)) {
			SetCursorPos(centerScreenX, centerScreenY);
		}

		Sleep(40); // sensibly arbitrary milliseconds
	}

	return 0;
}
