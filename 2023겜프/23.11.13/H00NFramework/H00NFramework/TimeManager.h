#pragma once

class TimeManager
{
	SINGLE(TimeManager)

public:
	void Init();
	void Update();

public:
	const float& GetDeltaTime() const { return deltaTime; }

private:
	float deltaTime;

private:
	LARGE_INTEGER previousCount;
	LARGE_INTEGER currentCount;
	LARGE_INTEGER frequency;

	UINT frameCount;
	UINT fps;
	float accumulateFrameTime;
};

