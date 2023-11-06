#pragma once

class Collider;

class Object
{
public:
	Object();
	virtual ~Object();

public:
	virtual void Update();
	virtual void FinalUpdate() final;
	virtual void Render(HDC hDC);

	void ComponentRender(HDC hDC);

public:
	void SetPosition(Vector2 position) { this->position = position; }
	void SetScale(Vector2 scale) { this->scale = scale; }

	const Vector2& GetPosition() const { return position; }
	const Vector2& GetScale() const { return scale; }

	Collider* GetCollider() const { return collider; }

public:
	void CreateCollider();

private:
	Vector2 position;
	Vector2 scale;

private:
	Collider* collider;
};

