#pragma once
#include "pch.h"
#include "Object.h"

class Core
{
	SINGLE(Core)

public:
	bool	Init(HWND hWnd);
	void	GameLoop();

private:
	void Update();
	void Render();

private:
	HDC		hDC;
	HWND	hWnd;
	Object	object;
};