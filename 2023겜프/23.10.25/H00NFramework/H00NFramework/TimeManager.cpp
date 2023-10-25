#include "pch.h"
#include "Core.h"
#include "TimeManager.h"

void TimeManager::Init()
{
	previousCount = {};
	currentCount = {};
	frequency = {};
	deltaTime = 0;

	frameCount = 0;
	fps = 0;
	accumulateFrameTime = 0;

	QueryPerformanceCounter(&previousCount);
	QueryPerformanceFrequency(&frequency);
}

void TimeManager::Update()
{
	QueryPerformanceCounter(&currentCount);

	deltaTime = (currentCount.QuadPart - previousCount.QuadPart) / (float)frequency.QuadPart;
	previousCount = currentCount;

	frameCount++;
	accumulateFrameTime += deltaTime;
	if (accumulateFrameTime >= 1)
	{
		fps = frameCount / accumulateFrameTime;
		accumulateFrameTime = 0;
		frameCount = 0;

		static wchar_t titleBuffer[100] = {};
		swprintf_s(titleBuffer, L"FPS : %d, DT : %f", fps, deltaTime);
		SetWindowText(Core::GetInstance()->GetHWnd(), titleBuffer);
	}
}
