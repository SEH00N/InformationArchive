#include "pch.h"
#include "Core.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "PathManager.h"
#include "ResManager.h"

bool Core::Init(HWND hWnd, POINT resolution)
{
	this->hWnd = hWnd;
	this->resolution = resolution;

	hBackBitmap = 0;
	hBackDC = 0;

	hDC = GetDC(hWnd);

	hBackBitmap = CreateCompatibleBitmap(hDC, resolution.x, resolution.y);
	hBackDC = CreateCompatibleDC(hDC);

	SelectObject(hBackDC, hBackBitmap);

	CreateGDI();
	// - manager init -
	PathManager::GetInstance()->Init();
	TimeManager::GetInstance()->Init();
	KeyManager::GetInstance()->Init();
	SceneManager::GetInstance()->Init();

	return true;
}

void Core::GameLoop()
{
	Update();
	Render();
}

void Core::Release()
{
	ReleaseDC(hWnd, hDC);
	DeleteDC(hBackDC);
	DeleteObject(hBackBitmap);

	for (int i = 0; i < (UINT)PenType::LAST; i++)
		DeleteObject(pens[i]);
	for (int i = 1; i < (UINT)BrushType::LAST; i++)
		DeleteObject(brushes[i]);

	ResManager::GetInstance()->Release();
}

void Core::Update()
{
	TimeManager::GetInstance()->Update();
	KeyManager::GetInstance()->Update();
	SceneManager::GetInstance()->Update();
}

void Core::Render()
{
	//Rectangle(hBackDC, -1, -1, resolution.x + 1, resolution.y + 1);
	PatBlt(hBackDC, 0, 0, resolution.x, resolution.y, WHITENESS);

	SceneManager::GetInstance()->Render(hBackDC);

	POINT mousepos = KeyManager::GetInstance()->GetMousePosition();
	static wchar_t mousebuf[100] = {};
	swprintf_s(mousebuf, L"Mouse: x :%d, y :%d", mousepos.x, mousepos.y);
	TextOut(hBackDC, 10, 10, mousebuf, wcslen(mousebuf));

	BitBlt(hDC, 0, 0, resolution.x, resolution.y, hBackDC, 0, 0, SRCCOPY);

	//Rectangle(hDC, 10, 10, 110, 110);
}

void Core::CreateGDI()
{
	brushes[(UINT)BrushType::Hollow] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	brushes[(UINT)BrushType::Red] = (HBRUSH)CreateSolidBrush(RGB(255, 167, 167));
	brushes[(UINT)BrushType::Green] = (HBRUSH)CreateSolidBrush(RGB(134, 229, 134));
	brushes[(UINT)BrushType::Blue] = (HBRUSH)CreateSolidBrush(RGB(103, 153, 255));
	brushes[(UINT)BrushType::Yellow] = (HBRUSH)CreateSolidBrush(RGB(255, 187, 0));
	//RED GREEN BLUE PEN
	pens[(UINT)PenType::Hollow] = CreatePen(PS_NULL, 0, RGB(0, 0, 0));
	pens[(UINT)PenType::Red] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	pens[(UINT)PenType::Green] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	pens[(UINT)PenType::Blue] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	pens[(UINT)PenType::Yellow] = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
}
