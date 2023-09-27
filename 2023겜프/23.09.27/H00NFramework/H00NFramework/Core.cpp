#include "pch.h"
#include "Core.h"

bool Core::Init(HWND hWnd)
{
	this->hWnd = hWnd;
	this->hDC = GetDC(hWnd);

	object.position = { 100, 100 };
	object.scale = { 100, 100 };

	return true;
}

void Core::GameLoop()
{
	static int count = 0;
	++count;
	static int prev = GetTickCount64();
	int cur = GetTickCount64();
	if (cur - prev > 1000)
	{
		prev = cur;
		count = 0;
	}

	Update();
	Render();
}

void Core::Update()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		object.position.x -= 1;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		object.position.x += 1;
}

void Core::Render()
{
	RECT_RENDER(hDC, object.position.x, object.position.y, object.scale.x, object.scale.y);
	//Rectangle(hDC, 10, 10, 110, 110);
}
