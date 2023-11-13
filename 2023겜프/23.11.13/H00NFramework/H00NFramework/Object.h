#pragma once

class Animator;
class Collider;

class Object
{
public:
	Object();
	virtual ~Object();

public:
	virtual void EnterCollision(Collider* other);
	virtual void StayCollision(Collider* other);
	virtual void ExitCollision(Collider* other);

public:
	virtual void Update();
	virtual void FinalUpdate() final;
	virtual void Render(HDC hDC);

	void ComponentRender(HDC hDC);

public:
	void SetPosition(Vector2 position) { this->position = position; }
	void SetScale(Vector2 scale) { this->scale = scale; }
	void SetName(std::wstring name) { this->name = name; }

	const Vector2& GetPosition() const { return position; }
	const Vector2& GetScale() const { return scale; }
	const std::wstring& GetName() const { return name; }
	const bool& GetAlive() const { return alive; }

	Collider* GetCollider() const { return collider; }

public:
	void CreateCollider();
	void CreateAnimator();

private:
	void SetDead() { alive = false; }
	friend class EventManager;

private:
	Vector2 position;
	Vector2 scale;
	std::wstring name;
	bool alive;

private:
	Collider* collider;
	Animator* animator;
};

