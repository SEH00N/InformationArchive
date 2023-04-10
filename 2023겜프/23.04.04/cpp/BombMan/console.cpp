#include "console.h"

void FullScreen()
{
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
}

void Go2xy(int x, int y)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cur = { x, y };

	SetConsoleCursorPosition(hOut, cur);
}

void ConsoleCursor(bool _bVls, DWORD _dwSize)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = _bVls;
	cursorInfo.dwSize = _dwSize;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void SetColor(int _color, int _bgColor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _bgColor << 4 | _color);
}
