#include "pch.h"
#include "Vector2.h"

Vector2::Vector2() : x{0}, y{0}
{
}

Vector2::Vector2(float x, float y): x{ x }, y{ y }
{
}

Vector2::Vector2(int x, int y) : x{ (float)x }, y{ (float)y }
{
}

Vector2::Vector2(POINT pt) : x{ (float)pt.x }, y{ (float)pt.y }
{
}

Vector2::Vector2(const Vector2& right) : x{ right.x }, y{ right.y }
{
}

Vector2::~Vector2()
{
}
