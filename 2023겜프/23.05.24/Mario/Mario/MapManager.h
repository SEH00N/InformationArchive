#pragma once

#include "define.h"

class Stage;

class MapManager
{
private:
	MapManager();
	~MapManager();

private:
	static MapManager* instance;

public:
	static MapManager* GetInstance()
	{
		if (instance == nullptr)
			instance = new MapManager();

		return instance;
	}

	static void DestroyInstance() { SAFE_DELETE(instance); }

private:
	Stage* stages[3];
	int	currentStage;

public:
	Stage* GetCurrentStage() { return stages[currentStage]; }

public:
	bool Init();
	void Run(int currentStage);
};

