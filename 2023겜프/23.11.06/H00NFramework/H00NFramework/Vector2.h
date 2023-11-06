#pragma once
#include <assert.h>

struct Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	Vector2(int x, int y);
	Vector2(POINT pt);
	Vector2(const Vector2& right);
	~Vector2();

public:
	float Length() { return sqrt(SqrLength()); }
	float SqrLength() { return Dot(*this, *this); }

	Vector2& Normalize() {
		float length = Length();
		assert(length != 0.f);

		x /= length;
		y /= length;
		return *this;
	}
	
public:
	static float Dot(const Vector2& left, const Vector2& right) {
		float x = left.x * right.x;
		float y = left.y * right.y;
		return x + y;
	}

public:
	float x;
	float y;

	Vector2 operator + (Vector2 _vOther)
	{
		return Vector2(x + _vOther.x, y + _vOther.y);
	}
	Vector2 operator - (Vector2 _vOther)
	{
		return Vector2(x - _vOther.x, y - _vOther.y);
	}
	Vector2 operator * (Vector2 _vOther)
	{
		return Vector2(x * _vOther.x, y * _vOther.y);
	}
	Vector2 operator / (Vector2 _vOther)
	{
		assert(!(0.f == _vOther.x || 0.f == _vOther.y));
		return Vector2(x / _vOther.x, y / _vOther.y);
	}
};

