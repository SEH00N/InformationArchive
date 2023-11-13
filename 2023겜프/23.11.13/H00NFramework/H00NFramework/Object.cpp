#include "pch.h"
#include "Object.h"
#include "Collider.h"
#include "Animator.h"

Object::Object() : position{}, scale{}, collider{nullptr}, alive{true}
{
}

Object::~Object()
{
	if (collider != nullptr)
		delete collider;
	if (animator != nullptr)
		delete animator;
}

void Object::EnterCollision(Collider* other)
{
}

void Object::StayCollision(Collider* other)
{
}

void Object::ExitCollision(Collider* other)
{
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

	if (animator)
		animator->Render(hDC);
}

void Object::CreateCollider()
{
	collider = new Collider();
	collider->owner = this;
}

void Object::CreateAnimator()
{
	animator = new Animator();
	animator->owner = this;
}
