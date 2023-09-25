#include "pch.h"
#include "Core.h"

bool Core::Init(HWND hWnd)
{
	this->hWnd = hWnd;
	this->hDC = GetDC(hWnd);

	return true;
}

void Core::GameLoop()
{
	Rectangle(hDC, 10, 10, 110, 110);
}
