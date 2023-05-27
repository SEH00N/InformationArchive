#pragma once

#include <windows.h>

#define SAFE_DELETE(p) if(p) { delete p; p = nullptr; }

#define WIDTH	50
#define HEIGHT	10

enum class StageBlockType
{
	Wall = '0',
	Road = '1',
	Start = '2',
	End = '3',
	COIN = '4'
};