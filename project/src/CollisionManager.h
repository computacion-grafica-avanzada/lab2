#pragma once

#include <vector>
#include "Collider.h"

class CollisionManager
{
private:
	std::vector<Collider*> objectsColliders;
	ColliderFloor* floorCollider;
	void solvePlayerCollisionWithFloor();
	float playerFeetPosOffset;
public:
	Collider* player;

	CollisionManager(Collider* player, ColliderFloor* floorCollider);
	~CollisionManager();
	void addObjectCollider(Collider* objectCollider);
	void removeObjectCollider(int id);
	void solvePlayerCollisions(bool flyMode);
	void setPlayerFeetPosOffset(float offset);
};

