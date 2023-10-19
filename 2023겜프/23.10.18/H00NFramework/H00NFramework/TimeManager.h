#pragma once
#include "pch.h"

class TimeManager
{
	SINGLE(TimeManager)

public:
	void Init();
	void Update();

private:
	LARGE_INTEGER previousCount;
};

