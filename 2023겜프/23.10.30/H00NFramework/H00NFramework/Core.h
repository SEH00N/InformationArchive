#pragma once

class Core
{
	SINGLE(Core)

public:
	bool	Init(HWND hWnd, POINT resolution);
	void	GameLoop();
	void	Release();

public:
	const HWND& GetHWnd() const { return hWnd; }
	const HDC& GetMainHDC() const { return hDC; }
	const Vector2& GetResolution() const { return resolution; }

private:
	void Update();
	void Render();

private:
	HWND	hWnd;
	HDC		hDC;

	HDC		hBackDC;
	HBITMAP	hBackBitmap;

	POINT	resolution;
};