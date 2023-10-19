#pragma once
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
	float x;
	float y;
};

