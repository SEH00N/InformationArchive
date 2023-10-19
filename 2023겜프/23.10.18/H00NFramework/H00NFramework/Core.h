#pragma once
#include "pch.h"
#include "Object.h"

class Core
{
	SINGLE(Core)

public:
	bool	Init(HWND hWnd, POINT resolution);
	void	GameLoop();

private:
	void Update();
	void Render();

private:
	HDC		hDC;
	HWND	hWnd;
	POINT	resolution;
	Object	object;
};