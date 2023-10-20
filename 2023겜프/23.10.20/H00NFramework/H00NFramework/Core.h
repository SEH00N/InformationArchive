#pragma once
#include "pch.h"
#include "Object.h"

class Core
{
	SINGLE(Core)

public:
	bool	Init(HWND hWnd, POINT resolution);
	void	GameLoop();
	void	Release();

public:
	const HWND& GetHWnd() const { return hWnd; }

private:
	void Update();
	void Render();

private:
	HWND	hWnd;
	HDC		hDC;

	HDC		hBackDC;
	HBITMAP	hBackBitmap;

	POINT	resolution;
	Object	object;
};