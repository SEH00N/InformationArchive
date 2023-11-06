#include "pch.h"
#include "Object.h"
#include "Collider.h"
#include "SelectGDI.h"

Collider::Collider() : owner{ nullptr }, scale{ Vector2{40.f, 40.f} }
{
}

Collider::~Collider()
{
}

void Collider::FinalUpdate()
{
	Vector2 pos = owner->GetPosition();
	final = pos + offset;
}

void Collider::Render(HDC hDC)
{
	SelectGDI pen(hDC, PenType::Green);
	SelectGDI brush(hDC, BrushType::Hollow);

	RECT_RENDER(hDC, final.x, final.y, scale.x, scale.y);
}
