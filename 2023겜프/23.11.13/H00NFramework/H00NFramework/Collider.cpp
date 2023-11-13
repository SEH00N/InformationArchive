#include "pch.h"
#include "Object.h"
#include "Collider.h"
#include "SelectGDI.h"

UINT Collider::NextID = 0;

Collider::Collider() : owner{ nullptr }, scale{ Vector2{40.f, 40.f} }, id{ NextID++ }
{
}

Collider::Collider(const Collider& origin) : owner{ origin.owner }, scale{ origin.scale }, offset{ origin.offset }, id{ NextID++ }
{
}

Collider::~Collider()
{
}

void Collider::EnterCollision(Collider* other)
{
	++check;
	owner->EnterCollision(other);
}

void Collider::StayCollision(Collider* other)
{
	owner->StayCollision(other);
}

void Collider::ExitCollision(Collider* other)
{
	--check;
	owner->ExitCollision(other);
}

void Collider::FinalUpdate()
{
	Vector2 pos = owner->GetPosition();
	final = pos + offset;
}

void Collider::Render(HDC hDC)
{
	PenType penType = PenType::Green;
	if(check)
		penType = PenType::Red;

	SelectGDI pen(hDC, penType);
	SelectGDI brush(hDC, BrushType::Hollow);

	RECT_RENDER(hDC, final.x, final.y, scale.x, scale.y);
}
