#pragma once
#include "pch.h"
#include "Object.h"

class Player : public Object
{
public:
	virtual void Update() override;
	//virtual void Render(HDC hDC) override;
};

