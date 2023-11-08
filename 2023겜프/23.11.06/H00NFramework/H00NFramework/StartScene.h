#pragma once
#include "Scene.h"

class StartScene : public Scene
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

