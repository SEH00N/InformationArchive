#include "pch.h"
#include "CollisionManager.h"

void CollisionManager::Update()
{
	for (UINT row = 0; row < (UINT)ObjectGroup::LAST; ++row)
		for (UINT col = row; col < (UINT)ObjectGroup::LAST; ++col)
			if (check[row] & (1 << col))
				CollisionGroupUpdate((ObjectGroup)row, (ObjectGroup)col); // 충돌 업데이트
}

void CollisionManager::CollisionGroupUpdate(ObjectGroup left, ObjectGroup right)
{
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
