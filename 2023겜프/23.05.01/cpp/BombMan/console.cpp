#include "console.h"

void FullScreen()
{
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
}

BOOL Go2xy(int x, int y)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cur = { x, y };

	return SetConsoleCursorPosition(hOut, cur);
}

BOOL Go2xyPlayer(int x, int y)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cur = { x * 2, y };

	return SetConsoleCursorPosition(hOut, cur);
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

int GetColor()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

	int color = info.wAttributes;
	return color;
}

int GetbgColor()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

	int color = info.wAttributes >> 4;
	return color;
}