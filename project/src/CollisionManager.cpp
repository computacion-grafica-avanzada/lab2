#include "CollisionManager.h"

CollisionManager::CollisionManager(Collider* player, ColliderFloor* floorCollider)
{
	this->player = player;
	this->floorCollider = floorCollider;
}

CollisionManager::~CollisionManager()
{
	delete(player);
	delete(floorCollider);
	for (int i = objectsColliders.size() - 1; i >= 0; i--)
	{
		delete(objectsColliders[i]);
		objectsColliders.pop_back();
	}
}

void CollisionManager::addObjectCollider(Collider* objectCollider)
{
	objectsColliders.push_back(objectCollider);
}

void CollisionManager::removeObjectCollider(int id)
{
	for (int i = 0; i < objectsColliders.size(); i++)
	{
		if (objectsColliders[i]->id == id)
		{
			objectsColliders.erase(objectsColliders.begin() + i);
			break;
		}
	}
}

void CollisionManager::solvePlayerCollisionWithFloor()
{
	float floorHeight = floorCollider->getHeightAtPos(player->pos);
	if (player->pos.y < floorHeight + player->radius)
	{
		player->pos.y = floorHeight + player->radius;
	}
}

void CollisionManager::solvePlayerCollisions()
{
	for (int i = 0; i < objectsColliders.size(); i++)
	{
		player->solveCollisionWithObject(objectsColliders[i]);
	}
	solvePlayerCollisionWithFloor();
}