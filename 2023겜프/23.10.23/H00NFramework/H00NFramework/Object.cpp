#include "pch.h"
#include "Object.h"

Object::Object() : position{}, scale{}
{
}

Object::~Object()
{
}

void Object::Update()
{

}

void Object::Render(HDC hDC)
{
	RECT_RENDER(hDC, position.x, position.y, scale.x, scale.y);
}
