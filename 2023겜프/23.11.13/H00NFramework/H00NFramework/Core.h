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

public:
	const HBRUSH& GetBrush(BrushType type) { return brushes[(UINT)type]; }
	const HPEN& GetPen(PenType type) { return pens[(UINT)type]; }

private:
	void Update();
	void Render();
	void CreateGDI();

private:
	HWND	hWnd;
	HDC		hDC;

	HDC		hBackDC;
	HBITMAP	hBackBitmap;

	POINT	resolution;

	HBRUSH	brushes[(UINT)BrushType::LAST];
	HPEN	pens[(UINT)PenType::LAST];
};