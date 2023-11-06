#pragma once

class Object;

class Collider
{
	friend class Object;

public:
	Collider();
	~Collider();

public:
	void SetScale(Vector2 scale) { this->scale = scale; }
	void SetOffset(Vector2 offset) { this->offset = offset; }
	const Vector2& GetScale() const { return scale; }
	const Vector2& GetOffset() const { return offset; }

private:
	Object* owner;
	Vector2 offset;
	Vector2 final;
	Vector2 scale;

public:
	void FinalUpdate();
	void Render(HDC hDC);
};
