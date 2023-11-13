#pragma once

union ColliderID
{
	struct
	{
		UINT LeftID;
		UINT RightID;
	};
	ULONGLONG ID;
};

class Collider;
class CollisionManager
{
	SINGLE(CollisionManager)
public:
	void Update();
	void CheckReset();
	void CheckGroup(ObjectGroup left, ObjectGroup right);
	 
private:
	void CollisionGroupUpdate(ObjectGroup left, ObjectGroup right);
	bool IsCollision(Collider* left, Collider* right);

private:
	UINT check[(UINT)ObjectGroup::LAST];
	std::map<ULONGLONG, bool> mapColInfo;
};

