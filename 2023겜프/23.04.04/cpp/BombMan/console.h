#pragma once

#include <windows.h>

enum class COLOR {
	BLACK,			BLUE,			GREEN,			SKYBLUE,
	RED,			VIOLET,			YELLOW,			LIGHT_GRAY,	
	GRAY,			LIGHT_BLUE,		LIGHT_GREEN,	MINT,
	LIGHT_RED,		LIGHT_VIOLET,	LIGHT_YELLOW,	WHITE
};

void FullScreen();
void Go2xy(int x, int y);
void ConsoleCursor(bool _bVls, DWORD _dwSize);
void SetColor(int _color, int _bgColor);