#include <Windows.h>
#include <iostream>
#include <vector>

#define TOPMOST_BIT_MASK 0b1000
#define TOP_BIT_MASK	 0b0000

typedef struct {
	HWND hwnd;
	std::string name;
} WindowInfo;
static std::vector<WindowInfo> windowList;

static BOOL CALLBACK enumWindowCallback(HWND hwnd, LPARAM lparam) {
	int length = GetWindowTextLength(hwnd);
	CHAR* buffer = new CHAR[length + 1];
	GetWindowTextA(hwnd, buffer, length + 1);
	std::string windowTitle(buffer);
	delete[] buffer;

	if (length != 0)
		windowList.push_back({ hwnd, windowTitle });

	return TRUE;
}

std::vector<WindowInfo> getActiveWindowsList() {
	windowList.clear();

	if (!EnumWindows(enumWindowCallback, NULL)) {
		exit(-1);
	}
	if (windowList.empty()) {
		exit(-1);
	}
	return windowList;
}


void main() {
	std::vector<WindowInfo> list = getActiveWindowsList();

	for (auto item : list) {
		LONG flags = GetWindowLongA(item.hwnd, GWL_EXSTYLE); // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowlonga we want to detect topmost so GWL_EXSTYLE is fitting.

		//Since WS_EX_TOPMOST is is set at bit 0b1000 and we using flags, TOP_BIT_MASK is not necessary
		if (flags & TOPMOST_BIT_MASK || flags & TOP_BIT_MASK) {
			if (IsWindowVisible(item.hwnd)) {
				std::cout << "Found a TOP-MOST window 2 " << item.name << std::endl;
			}


		}
	}
	while(1){}
}
