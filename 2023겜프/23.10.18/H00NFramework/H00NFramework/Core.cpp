#include "pch.h"
#include "Core.h"

bool Core::Init(HWND hWnd, POINT resolution)
{
	this->hWnd = hWnd;
	this->hDC = GetDC(hWnd);
	this->resolution = resolution;

	object.SetPosition(Vector2({ resolution.x / 2, resolution.y / 2 }));
	object.SetScale({ 100, 100 });

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
	Vector2 position = object.GetPosition();

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		position.x -= 0.01f;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		position.x += 0.01f;

	object.SetPosition(position);
}

void Core::Render()
{
	Vector2 pos = object.GetPosition();
	Vector2 scale = object.GetScale();
	RECT_RENDER(hDC, pos.x, pos.y, scale.x, scale.y);
	//Rectangle(hDC, 10, 10, 110, 110);
}
