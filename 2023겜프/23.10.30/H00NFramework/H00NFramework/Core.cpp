#include "pch.h"
#include "Core.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "PathManager.h"

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
