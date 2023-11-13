#include "pch.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "Object.h"
#include "Scene.h"
#include "Collider.h"

void CollisionManager::Update()
{
	for (UINT row = 0; row < (UINT)ObjectGroup::LAST; ++row)
		for (UINT col = row; col < (UINT)ObjectGroup::LAST; ++col)
			if (check[row] & (1 << col))
				CollisionGroupUpdate((ObjectGroup)row, (ObjectGroup)col); // 충돌 업데이트
}

void CollisionManager::CollisionGroupUpdate(ObjectGroup left, ObjectGroup right)
{
	std::shared_ptr<Scene> currentScene = SceneManager::GetInstance()->GetCurrentScene();
	const std::vector<Object*>& leftObj = currentScene->GetGroupObject(left);
	const std::vector<Object*>& rightObj = currentScene->GetGroupObject(right);

	for (int i = 0; i < leftObj.size(); ++i)
	{
		if (leftObj[i]->GetCollider() == nullptr)
			continue;
			
		for (int j = 0; j < rightObj.size(); ++j)
		{
			if (nullptr == rightObj[j]->GetCollider() || leftObj[i] == rightObj[j])
				continue;

			Collider* leftCollider = leftObj[i]->GetCollider();
			Collider* rightCollider = rightObj[j]->GetCollider();
			
			ColliderID colID;
			colID.LeftID = leftCollider->GetID();
			colID.RightID = rightCollider->GetID();

			auto iter = mapColInfo.find(colID.ID);
			if (iter == mapColInfo.end())
			{
				mapColInfo.insert({ colID.ID, false });
				iter = mapColInfo.find(colID.ID);
			}

			if (IsCollision(leftCollider, rightCollider))
			{
				if (iter->second)
				{
					leftCollider->StayCollision(rightCollider);
					rightCollider->StayCollision(leftCollider);
				}
				else
				{
					leftCollider->EnterCollision(rightCollider);
					rightCollider->EnterCollision(leftCollider);
					iter->second = true;
				}
			}
			else
			{
				if (iter->second)
				{
					leftCollider->ExitCollision(rightCollider);
					rightCollider->ExitCollision(leftCollider);
					iter->second = false;
				}
			}
		}
	}
}

bool CollisionManager::IsCollision(Collider* left, Collider* right)
{
	Vector2 leftPos = left->GetFinalPos();
	Vector2 rightPos = right->GetFinalPos();
	Vector2 leftScale = left->GetScale();
	Vector2 rightScale = right->GetScale();
	
	if(abs(rightPos.x - leftPos.x) < (leftScale.x + rightScale.x) / 2.f &&
	   abs(rightPos.y - leftPos.y) < (leftScale.y + rightScale.y) / 2.f)
		return true;

	return false;
}

void CollisionManager::CheckReset()
{
	memset(check, 0, sizeof(UINT) * (UINT)ObjectGroup::LAST);
}

void CollisionManager::CheckGroup(ObjectGroup left, ObjectGroup right)
{
	UINT row = (UINT)left;
	UINT col = (UINT)right;

	if (row > col)
		std::swap(row, col);

	if (check[row] & (1 << col))
		check[row] &= ~(1 << col);
	else
		check[row] |= (1 << col);
}
