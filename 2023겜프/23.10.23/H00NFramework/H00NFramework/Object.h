#pragma once
class Object
{
public:
	Object();
	virtual ~Object();

public:
	virtual void Update();
	virtual void Render(HDC hDC);

public:
	void SetPosition(Vector2 position) { this->position = position; }
	void SetScale(Vector2 scale) { this->scale = scale; }

	const Vector2& GetPosition() const { return position; }
	const Vector2& GetScale() const { return scale; }

private:
	Vector2 position;
	Vector2 scale;
};

