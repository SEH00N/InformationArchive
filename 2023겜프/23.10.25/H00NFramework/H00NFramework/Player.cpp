#include "pch.h"
#include "Player.h"

#include "TimeManager.h"
#include "KeyManager.h"
#include "SceneManager.h"

void Player::Update()
{
	Vector2 position = GetPosition();

	if (GetKeyPress(KeyType::Left))
		position.x -= 1000 * DeltaTime;
	if (GetKeyPress(KeyType::Right))
		position.x += 1000 * DeltaTime;

	SetPosition(position);
}