#pragma once
#include <glm/glm.hpp>
#include "ColliderFloor.h"

enum ColliderType { sphere, box, capsule };

class Collider
{
public:
	int id;
	ColliderType type;
	// Zero mass means static object
	float mass;
	glm::vec3 pos;
	// Used by spheres and capsules
	float radius;
	// Used by boxes
	float width, depth;
	// Used by boxes and capsules
	float height;

	// Sphere constructor
	Collider(int id, float mass, float radius);
	// Box constructor
	Collider(int id, float mass, float width, float height, float depth);
	// Cylinder constructor
	Collider(int id, float mass, float radius, float height);

	static void solveCollisionSphereSphere(Collider* s1, Collider* s2);
	static void solveCollisionBoxBox(Collider* b1, Collider* b2);
	static void solveCollisionSphereBox(Collider* s, Collider* b);
	static void solveCollisionSphereCapsule(Collider* s, Collider* b);
	void solveCollisionWithObject(Collider* objectCollider);
	void solveCollisionWithFloor(ColliderFloor* floor);
};

