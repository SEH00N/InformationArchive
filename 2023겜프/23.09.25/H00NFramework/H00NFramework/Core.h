#pragma once
#include "pch.h"

class Core
{
	SINGLE(Core)

public:
	bool	Init(HWND hWnd);
	void	GameLoop();

private:
	HDC		hDC;
	HWND	hWnd;
};