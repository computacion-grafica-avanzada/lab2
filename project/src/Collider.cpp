#include "Collider.h"
#include "Math.h"

// Sphere constructor
Collider::Collider(int id, float mass, float radius)
{
	this->id = id;
	this->mass = mass;
	this->radius = radius;
	this->type = sphere;
	this->pos = glm::vec3(0);

	this->width = 0;
	this->height = 0;
	this->depth = 0;
}

// Box constructor
Collider::Collider(int id, float mass, float width, float height, float depth)
{
	this->id = id;
	this->mass = mass;
	this->width = width;
	this->height = height;
	this->depth = depth;
	this->type = box;
	this->pos = glm::vec3(0);

	this->radius = 0;
}

// Capsule constructor
Collider::Collider(int id, float mass, float radius, float height)
{
	this->id = id;
	this->mass = mass;
	this->radius = radius;
	this->height = height;
	this->type = capsule;
	this->pos = glm::vec3(0);

	this->width = 0;
	this->depth = 0;
}

// Reference
// https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection

void Collider::solveCollisionSphereSphere(Collider* s1, Collider* s2)
{
	if (s1->type != sphere || s2->type != sphere)
	{
		return;
	}

	// Checks if the collision exists.
	if (Math::distSquared(s1->pos, s2->pos) < (s1->radius + s2->radius) * (s1->radius + s2->radius))
	{
		printf("\nCollision detected!");

		glm::vec3 newDist = glm::normalize(s1->pos - s2->pos) * (s1->radius + s2->radius);
		// The lighter object corrects its position
		if (s1->mass == 0 || (s1->mass > s2->mass && s2->mass != 0))
		{
			s2->pos.x = s1->pos.x - newDist.x;
			s2->pos.z = s1->pos.z - newDist.z;
		}
		else
		{
			s1->pos.x = s2->pos.x + newDist.x;
			s1->pos.z = s2->pos.z + newDist.z;
		}
	}
}

void Collider::solveCollisionBoxBox(Collider* b1, Collider* b2)
{
	if (b1->type != box || b2->type != box)
	{
		return;
	}

	// We assume both boxes are aligned.

	// Checks intersections in every axis.
	bool xAxisCollision = Math::checkRangesIntersection(b1->pos.x - b1->width / 2, b1->pos.x + b1->width / 2, b2->pos.x - b2->width / 2, b2->pos.x + b2->width / 2);
	bool yAxisCollision = Math::checkRangesIntersection(b1->pos.y - b1->height / 2, b1->pos.y + b1->height / 2, b2->pos.y - b2->height / 2, b2->pos.y + b2->height / 2);
	bool zAxisCollision = Math::checkRangesIntersection(b1->pos.z - b1->depth / 2, b1->pos.z + b1->depth / 2, b2->pos.z - b2->depth / 2, b2->pos.z + b2->depth / 2);

	// Checks if the collision exists.
	if (xAxisCollision && yAxisCollision && zAxisCollision)
	{
		// The lighter object corrects its position
		if (b1->mass == 0 || (b1->mass > b2->mass && b2->mass != 0))
		{
			// TODO: resolver colision
		}
		else
		{
			// TODO: resolver colision
		}
	}
}

void Collider::solveCollisionSphereBox(Collider* s, Collider* b)
{
	if (s->type != sphere || b->type != box)
	{
		return;
	}

	glm::vec3 closestPoint;
	// get box closest point to sphere center by clamping
	closestPoint.x = std::max(b->pos.x - b->width / 2.0f, std::min(s->pos.x, b->pos.x + b->width / 2.0f));
	closestPoint.y = std::max(b->pos.y - b->height / 2.0f, std::min(s->pos.y, b->pos.y + b->height / 2.0f));
	closestPoint.z = std::max(b->pos.z - b->depth / 2.0f, std::min(s->pos.z, b->pos.z + b->depth / 2.0f));

	// this is the same as the sphere-sphere collision detection
	float distSq = Math::distSquared(closestPoint, s->pos);

	float radiusSq = s->radius;
	radiusSq *= radiusSq;

	// Checks if the collision exists.
	if (distSq < radiusSq)
	{
		printf("\nCollision detected!");
		glm::vec3 intersec = glm::normalize(closestPoint - s->pos) * (s->radius - std::sqrt(distSq));
		//printf("\nIntersec: (%.6f, %.6f, %.6f)", intersec.x, intersec.y, intersec.z);

		// The lighter object corrects its position
		if (s->mass == 0 || (s->mass > b->mass && b->mass != 0))
		{
			b->pos += intersec;
		}
		else
		{
			s->pos -= intersec;
		}
	}
}

void Collider::solveCollisionSphereCapsule(Collider* s, Collider* c)
{
	if (s->type != sphere || c->type != capsule)
	{
		return;
	}

	// Checks if the collision exists.
	if (Math::distXZSquared(s->pos, c->pos) < (s->radius + c->radius) * (s->radius + c->radius) &&
		abs(s->pos.y - c->pos.y) < s->radius + c->height + c->radius)
	{
		printf("\nCollision detected!");

		// Solve the collision as if it was with a ball at the top/bottom of the capsule
		if (abs(s->pos.y - c->pos.y) > s->radius + c->height / 2.0f)
		{
			printf("\nCase limits");

			glm::vec3 extremePos;
			// Sphere at the top of the capsule
			if (s->pos.y > c->pos.y)
			{
				extremePos = glm::vec3(c->pos.x, c->pos.y + c->height / 2.0f, c->pos.z);
			}
			else
			{
				extremePos = glm::vec3(c->pos.x, c->pos.y - c->height / 2.0f, c->pos.z);
			}

			glm::vec3 newDist = glm::normalize(s->pos - extremePos) * (s->radius + c->radius);
			// The lighter object corrects its position
			if (s->mass == 0 || (s->mass > c->mass && c->mass != 0))
			{
				c->pos = s->pos - newDist;
			}
			else
			{
				s->pos = extremePos + newDist;
			}
		}
		// Solve the collision as if it was with a ball at the same height of the sphere
		else
		{
			printf("\nCase middle");

			glm::vec3 imaginarySpherePos;
			// Sphere at the same height of the other sphere
			imaginarySpherePos = glm::vec3(c->pos.x, s->pos.y, c->pos.z);

			glm::vec3 newDist = glm::normalize(s->pos - imaginarySpherePos) * (s->radius + c->radius);
			// The lighter object corrects its position
			if (s->mass == 0 || (s->mass > c->mass && c->mass != 0))
			{
				c->pos = s->pos - newDist;
			}
			else
			{
				s->pos = imaginarySpherePos + newDist;
			}
		}
	}
}


void Collider::solveCollisionWithObject(Collider* objectCollider)
{
	switch (type)
	{
	case sphere:
		if (objectCollider->type == sphere)
		{
			solveCollisionSphereSphere(this, objectCollider);
		}
		else if (objectCollider->type == box)
		{
			solveCollisionSphereBox(this, objectCollider);
		}
		break;
	case box:
		if (objectCollider->type == sphere)
		{
			solveCollisionSphereBox(objectCollider, this);
		}
		else if (objectCollider->type == box)
		{
			solveCollisionBoxBox(this, objectCollider);
		}
		break;
	default:
		solveCollisionSphereSphere(this, objectCollider);
		break;
	}
}

