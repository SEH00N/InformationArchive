#include "pch.h"
#include "Object.h"
#include "Collider.h"

Object::Object() : position{}, scale{}, collider{nullptr}
{
}

Object::~Object()
{
	if (collider != nullptr)
		delete collider;
}

void Object::Update()
{

}

void Object::FinalUpdate()
{
	if (collider)
		collider->FinalUpdate();
}

void Object::Render(HDC hDC)
{
	RECT_RENDER(hDC, position.x, position.y, scale.x, scale.y);
}

void Object::ComponentRender(HDC hDC)
{
	if(collider)
		collider->Render(hDC);
}

void Object::CreateCollider()
{
	collider = new Collider();
	collider->owner = this;
}
