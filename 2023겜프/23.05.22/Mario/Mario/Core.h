#pragma once

#include "define.h"

class Core
{
private:
	Core();

private:
	static Core* instance;

public:
	static Core* GetInstance()
	{
		if (instance == nullptr)
			instance = new Core();
		
		return instance;
	}

	static void DestroyInstance()
	{
		SAFE_DELETE(instance);
	}

public:
	bool Init();
	void Run();
	int MenuDraw();
};