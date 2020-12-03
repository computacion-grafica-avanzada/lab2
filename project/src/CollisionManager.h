#pragma once

#include <vector>
#include "Collider.h"

class CollisionManager
{
private:
	std::vector<Collider*> objectsColliders;
	ColliderFloor* floorCollider;
public:
	Collider* player;

	CollisionManager(Collider* player, ColliderFloor* floorCollider);
	~CollisionManager();
	void addObjectCollider(Collider* objectCollider);
	void removeObjectCollider(int id);
	void solvePlayerCollisionWithFloor();
	void solvePlayerCollisions();
};

