#include <Windows.h>
#include <iostream>

void main(void) {
	while (1) {
		SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		Sleep(10); // Dont hammer the cpu
	}
}