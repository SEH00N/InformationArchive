#pragma once
#include "Object.h"
class Bullet :
    public Object
{
public:
    Bullet();
    ~Bullet();

public:
    void Update() override;
    void Render(HDC hDC) override;

public:
    void SetDirection(float theta) { this->theta = theta; }
    void SetDirection(Vector2 dir) { this->direction = dir.Normalize(); }

private:
    float theta;
    Vector2 direction;
};

