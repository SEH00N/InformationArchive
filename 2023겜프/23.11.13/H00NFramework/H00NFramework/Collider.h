#pragma once

class Object;

class Collider
{
	friend class Object;

public:
	Collider();
	Collider(const Collider& origin);
	~Collider();
	Collider& operator = (Collider& origin) = delete;

public:
	void EnterCollision(Collider* other);
	void StayCollision(Collider* other);
	void ExitCollision(Collider* other);

public:
	void SetScale(Vector2 scale) { this->scale = scale; }
	void SetOffset(Vector2 offset) { this->offset = offset; }
	const Vector2& GetScale() const { return scale; }
	const Vector2& GetOffset() const { return offset; }
	const Vector2& GetFinalPos() const { return final; }
	const UINT& GetID() const { return id; }
	const Object* GetOwner() const { return owner; }
private:
	Object* owner;
	Vector2 offset;
	Vector2 final;
	Vector2 scale;
	UINT id;
	static UINT NextID;

	UINT check;

public:
	void FinalUpdate();
	void Render(HDC hDC);
};
