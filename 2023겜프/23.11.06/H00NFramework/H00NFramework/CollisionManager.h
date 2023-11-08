#pragma once
class CollisionManager
{
	SINGLE(CollisionManager)
public:
	void Update();
	void CheckReset();
	void CheckGroup(ObjectGroup left, ObjectGroup right);

private:
	void CollisionGroupUpdate(ObjectGroup left, ObjectGroup right);

private:
	UINT check[(UINT)ObjectGroup::LAST];
};

